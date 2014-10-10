#include "/d/Empire/empire.h"

#define P_ACHIEVEMENT(name) ("emp_achievement_" + (name))

inherit I_DAEMON;

public mapping _first;

static void create() {
    ::create();
    _first = 0;
}

static void reset(int flag) {
    ::reset(flag);
    if (!flag) {
        restore_object(EMP_DIR_VAR + "achievementd");
	if (!mapp(_first)) {
	    _first = ([ ]);
	}
    }
}

private int encode_progress(int val, int max) {
    if (val > 0x7fff || max > 0x7fff) {
        error("Value out of range.");
    }
    return (1 << 31) + (max << 16) + val;
}

private int decode_value(int val) {
    if (val >= 0) {
        return val; /* sign bit not set, old format */
    }
    return val & 0x7fff;
}

private int decode_limit(int val) {
    if (val >= 0) {
        return 100; /* sign bit not set, old format */
    }
    return (val >> 16) & 0x7fff;
}

private int decode_progress(int val) {
    return (100 * decode_value(val)) / decode_limit(val);
}

public string query_title(string achivement) {
    return capitalize(replace_string(achivement, "_", " "));
}

public string query_desc(string name) {
    return read_file(EMP_DIR_ETC_ACHIEVEMENTS + name);
}

private void notify_unlock(object ply, string name) {
    string out, desc;
    out  = sprintf("[ %|75s ]\n", "ACHIEVEMENT UNLOCKED:");
    out += sprintf("[ %75s ]\n", "");
    out += sprintf("[ %|75s ]\n", query_title(name));
    if (stringp(desc = query_desc(name))) {
        string *arr;
        int i, len;
        out += sprintf("[ %75s ]\n", "");        
        arr = explode(break_string(desc, 75), "\n");
        for (i = 0, len = sizeof(arr); i < len; ++i) {
            out += sprintf("[ %-75s ]\n", arr[i]);
        }
    }
    tell_object(ply, "\n" + out + "\n");
    EMP_D_LOG->log("achievements", ply->query_real_name() + 
                   " unlocked '" + name + "'");
}

public mapping query_achievements(object ply) {
    mapping dat, ret;
    string *arr;
    int i, len;
    if (!objectp(ply)) {
        return 0;
    }
    ret = ([ ]);
    dat = ply->query_m_property();
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        string val;
	if (!sscanf(arr[i], P_ACHIEVEMENT("%s"), val)) {
            continue;
        }
        ret[val] = decode_progress(dat[arr[i]]);
    }
    return ret;
}

public int query_achievement(object ply, string name) {
    if (!objectp(ply) || !stringp(name)) {
	return 0;
    }
    return decode_progress(ply->query_property(P_ACHIEVEMENT(name)));
}

public int has_achievement(object ply, string name) {
    return query_achievement(ply, name) >= 100;
}

public int query_num_unlocked(object ply) {
    mapping dat;
    string *arr;
    int i, len, ret;
    if (!mapp(dat = query_achievements(ply))) {
        return 0;
    }
    ret = 0;
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        if (dat[arr[i]] >= 100) {
            ++ret;
        }
    }
    return ret;
}

public varargs int try_unlock(object ply, string name, int val, int limit) {
    int prev;
    if (!objectp(ply) || !stringp(name)) {
	return 0;
    }
    if (has_achievement(ply, name)) {
	return 1;
    }
    ply->add_property(P_ACHIEVEMENT(name), encode_progress(val, limit));
    if (val < limit) {
	return 0;
    }
    notify_unlock(ply, name);
    if (arrayp(_first[name]) || ply->query_level() > ETERNAL_LAST) {
        return 1;
    }
    _first[name] = ({ ply->query_real_name(), time() });
    save_object(EMP_DIR_VAR + "achievementd");
    return 1;
}

public varargs int add_unlock(object ply, string name, int val, int limit) {
    val += decode_value(ply->query_property(P_ACHIEVEMENT(name)));
    return try_unlock(ply, name, val, limit);
}

public int unlock(object ply, string name) {
    return try_unlock(ply, name, 100, 100);
}

public void remove_achievement(object ply, string name) {
    ply->remove_property(P_ACHIEVEMENT(name));
}

public void clear_achievements(object ply) {
    string *arr;
    int i, len;
    arr = keys(query_achievements(ply));
    for (i = 0, len = sizeof(arr); i < len; ++i) {
	remove_achievement(ply, arr[i]);
    }
}

public mixed query_first(string name) {
    return _first[name];
}

public mapping query_firsts() {
    return _first;
}
