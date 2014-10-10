#include "/d/Empire/empire.h"

#define P_PROGRESS(name)   (_prefix + (name))
#define FLAG_HIDDEN        (0x01)
#define FLAG_UNIQUE        (0x02)

inherit daemon EMP_I_DAEMON;
inherit graph  EMP_I_GRAPH;

private string  _item_dir;
private string  _save_file;
private string  _prefix;
private mapping _titles;     /* ([ "item"  : "title"           ]) */
private mapping _descs;      /* ([ "item"  : "desc"            ]) */
private mapping _flags;      /* ([ "item"  : FLAG_X | FLAG_Y   ]) */
private mapping _locked_by;  /* ([ "item"  : ({ "item", ... }) ]) */
private mapping _hidden_by;  /* ([ "item"  : ({ "item", ... }) ]) */
private mapping _groups;     /* ([ "group" : ({ "item", ... }) ]) */
public  mapping _first_name; /* ([ "item"  : "player"          ]) */
public  mapping _first_time; /* ([ "item"  : time()            ]) */

public nomask varargs int query_num_unlocked(object ply, string *arr);
public nomask varargs int try_unlock(object ply, string str, int val, int lim);
public nomask int is_blocked(string item);

static void 
notify_unlock(object ply, string item) 
{
    /* empty */
}

static void 
create() 
{
    daemon::create();
    graph::create();
    _item_dir   = 0;
    _save_file  = 0;
    _prefix     = "emp_unlock_";
    _titles     = ([ ]);
    _descs      = ([ ]);
    _flags      = ([ ]);
    _locked_by  = ([ ]);
    _hidden_by  = ([ ]);
    _groups     = ([ ]);
    _first_name = ([ ]);
    _first_time = ([ ]);
    add_hook("__reset", store_fp("on_reset"));
}   

static nomask int
parse_tags(string str, string item) 
{
    string val, *arr;
    if (!stringp(str) || strlen(str) == 0 || str[0] != '@') {
        return 1;
    } 
    str = trim(str);
    if (str == "@unique") {
        _flags[item] = _flags[item] | FLAG_UNIQUE;
    } else if (str == "@hidden") {
        _flags[item] = _flags[item] | FLAG_HIDDEN;
    } else if (sscanf(str, "@title %s", val)) {
        _titles[item] = val;
    } else if (sscanf(str, "@hidden_by %s", val)) {
        if (!arrayp(arr = _hidden_by[item])) {
            arr = ({ });
        }
        _hidden_by[item] = arr + explode(val, " ") - ({ "" });
    } else if (sscanf(str, "@locked_by %s", val)) {
        if (!arrayp(arr = _locked_by[item])) {
            arr = ({ });
        }
        _locked_by[item] = arr + explode(val, " ") - ({ "" });
    } else if (sscanf(str, "@group %s", val)) {
        if (!arrayp(arr = _groups[val])) {
            arr = ({ });
        }
        _groups[val] = arr + ({ item });
    } else {
        error("Unsupported tag '" + str + "' declared in item '" + 
              item + "'.");
    }
    return 0;
}

private void 
init_items() 
{
    string *arr;
    int i, len;
    for (i = 0, len = sizeof(arr = get_files(_item_dir)); i < len; ++i) {
        string item, file;
        item = arr[i];
        file = read_file(_item_dir + item);
        _titles[item] = capitalize(replace_string(item, "_", " "));
        _descs[item] = implode(filter_array(explode(file, "\n"), "parse_tags", 
                                            this_object(), item), " ");
    }
}

private void 
init_saved() 
{
    restore_object(_save_file);
    if (!mapp(_first_name) || !mapp(_first_time)) {
        _first_name = ([ ]);
        _first_time = ([ ]);
    } 
}

static nomask void 
on_reset(int flag) 
{
    if (flag) {
        return;
    }
    if (stringp(_item_dir)) {
        init_items();
        assert_acyclic(_hidden_by);
        assert_acyclic(_locked_by);
    }
    if (stringp(_save_file)) {
        init_saved();
    }
}

private int 
encode_progress(int val, int max) 
{
    if (val < 0 || val > 0x7FFFFF) {
        error("Value out of [0, 0x7FFFFF] range; " + val);
    }
    if (max < 1 || max > 0x7FFFFF) {
        error("Limit out of [1, 0x7FFFFF] range; " + max);
    }
    return (((100 * val) / max) << 25) + val; 
}

private int 
decode_value(int val) 
{
    return max(0, val & 0x7FFFFF);
}

private int 
decode_progress(int val) 
{
    return max(0, val >> 25);
}

public nomask varargs mixed 
query_progress(object ply, string item) 
{
    mapping dat, ret;
    string *arr;
    int i, len;
    if (!objectp(ply)) {
        return 0;
    }
    if (stringp(item)) {
        return decode_progress(ply->query_property(P_PROGRESS(item)));
    }
    ret = ([ ]);
    for (i = 0, len = sizeof(arr = keys(_titles)); i < len; ++i) {
        ret[arr[i]] = query_progress(ply, arr[i]);
    }
    return ret;
}

public nomask int 
is_unlocked(object ply, mixed arg) 
{
    if (stringp(arg)) {
        return query_progress(ply, arg) == 100;
    }
    if (arrayp(arg)) {
        return query_num_unlocked(ply, arg) == sizeof(arg);
    }
    return 0;
}

public nomask varargs int 
query_num_unlocked(object ply, string *items) 
{
    int i, len, ret;
    if (!arrayp(items)) {
        items = keys(_titles);
    }
    ret = 0;
    for (i = 0, len = sizeof(items); i < len; ++i) {
        if (is_unlocked(ply, items[i])) {
            ++ret;
        }
    }
    return ret;
}

private void 
try_composites(object ply, string unlocked) 
{
    string *items;
    int i, len;
    for (i = 0, len = sizeof(items = keys(_locked_by)); i < len; ++i) {
        string item, *children;
        int val;
        if (!stringp(item = items[i]) ||
            !arrayp(children = _locked_by[item]) ||
            !sizeof(children & ({ unlocked })))
        {
            continue;
        }
        try_unlock(ply, item, query_num_unlocked(ply, children),
                   sizeof(children));
    }
}

public nomask varargs int 
try_unlock(object ply, string item, int val, int limit) 
{
    int prev;
    if (!objectp(ply) || !stringp(item)) {
	return 0;
    }
    EMP_DEBUG(ply, sprintf("try_unlock(%s, %d, %d)", item, val, limit));
    if (is_unlocked(ply, item)) {
        EMP_DEBUG(ply, "already unlocked");
	return 1;
    }
    if (val > limit) {
        val = limit;
    }
    if (is_blocked(item) && val == limit) {
        val = limit - 1;
    }
    ply->add_property(P_PROGRESS(item), encode_progress(val, limit));
    if (val < limit) {
        EMP_DEBUG(ply, val + " < " + limit);
	return 0;
    }
    notify_unlock(ply, item);
    if (!stringp(_first_name[item]) && !wizardp(ply)) {
        _first_name[item] = ply->query_real_name();
        _first_time[item] = time();
        if (stringp(_save_file)) {
            save_object(_save_file);
        }
    }
    try_composites(ply, item);
    return 1;
}

public nomask varargs int 
add_unlock(object ply, string item, int val, int limit) 
{
    val += decode_value(ply->query_property(P_PROGRESS(item)));
    return try_unlock(ply, item, val, limit);
}

public nomask int 
unlock(object ply, string item) 
{
    return try_unlock(ply, item, 100, 100);
}

public nomask void 
remove_item(object ply, string item) 
{
    ply->remove_property(P_PROGRESS(item));
}

public nomask void 
clear_items(object ply) 
{
    string *arr;
    int i, len;
    arr = ply->query_property();
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        string str;
        if (!sscanf(arr[i], _prefix + "%s", str)) {
            continue;
        }
	remove_item(ply, str);
    }
}

public nomask void 
set_item_dir(string val) 
{
    _item_dir = val;
}

public nomask string 
query_item_dir() 
{
    return _item_dir;
}

public nomask void 
set_save_file(string val) 
{
    _save_file = val;
}

public nomask string 
query_save_file() 
{
    return _save_file;
}

public nomask void 
set_prefix(string val) 
{
    _prefix = val;
}

public nomask string 
query_prefix() 
{
    return _prefix;
}

public nomask string *
query_items() 
{
    return keys(_titles);
}

public nomask string
query_item_by_title(string title) 
{
    string *arr;
    int i, len;
    title = lower_case(title);
    for (i = 0, len = sizeof(arr = keys(_titles)); i < len; ++i) {
        if (title == lower_case(_titles[arr[i]])) {
            return arr[i];
        }
    }
    return 0;
}

public nomask string 
query_title(string item) 
{
    string str;
    if (stringp(str = _titles[item])) {
        return str;
    }
    return capitalize(replace_string(item, "_", " "));
}

public nomask string 
query_desc(string item) 
{
    return _descs[item];
}

public nomask int 
is_hidden(string item) 
{
    return _flags[item] & FLAG_HIDDEN;
}

public nomask int 
is_unique(string item) 
{
    return _flags[item] & FLAG_UNIQUE;
}

public nomask int
is_blocked(string item) 
{
    return is_unique(item) && stringp(_first_name[item]);
}

public nomask string *
query_locked_by(string item) 
{
    return _locked_by[item];
}

public nomask string *
query_hidden_by(string item) 
{
    return _hidden_by[item];
}

public nomask string *
query_groups() 
{
    return keys(_groups);
}

public nomask string *
query_group(string group) 
{
    return _groups[group];
}

public nomask string 
query_group_of(string item) 
{
    string *arr;
    int i, len;
    for (i = 0, len = sizeof(arr = keys(_groups)); i < len; ++i) {
        if (sizeof(_groups[arr[i]] & ({ item }))) {
            return arr[i];
        }
    }
    return 0;
}

public nomask string 
query_first_name(string item) 
{
    return _first_name[item];
}

public nomask int 
query_first_time(string item) 
{
    return _first_time[item];
}

public nomask int 
can_see(object ply, string item) 
{
    string *arr;
    if (is_unlocked(ply, item)) {
        return 1;
    }
    if (is_hidden(item)) {
        return 0;
    }
    if (arrayp(arr = _hidden_by[item]) && !is_unlocked(ply, arr)) {
        return 0;
    }
    return 1;
}

public nomask string
render_groups() 
{
    return render_forest(_groups);
}

public nomask string
render_hidden_by() 
{
    return render_forest(create_forest(keys(_titles), _hidden_by));
}

public nomask string
render_locked_by() 
{
    return render_forest(create_forest(keys(_locked_by), _locked_by));
}
