#include "/d/Empire/empire.h"

inherit EMP_I_DAEMON;

private mapping _races;

static void
create()
{
    ::create();
    _races = ([ ]);
}

static string *
to_token_array(string str)
{
    return explode(strlen(str = trim(str)) ? str : " ", ",");
}

static string **
to_token_arrays(string str)
{
    return map_array(explode(str, "\n"), "to_token_array");
}

private string **
merge_token_arrays(string **lhs, string **rhs)
{
    int i, len;
    for (i = 0, len = sizeof(rhs); i < len; ++i) {
        if (i < sizeof(lhs)) {
            lhs[i] += rhs[i];
        } else {
            lhs += ({ rhs[i] });
        }
    }
    return lhs;
}

private string **
load_race(string race)
{
    int i, len;
    string *arr, **out, str;
    arr = get_files(EMP_DIR_ETC_NAMES + race) +
          get_files(EMP_DIR_ETC_NAMES + race + ".*");
    len = sizeof(arr);
    if (len == 0) {
        return 0;
    }
    out = ({ });
    for (i = 0; i < len; ++i) {
        if (!stringp(str = read_file(EMP_DIR_ETC_NAMES + arr[i]))) {
            continue;
        }
        out = merge_token_arrays(out, to_token_arrays(str));
    }
    _races[race] = out;
    return out;
}

public string
query_name(string race)
{
    string **dat, out;
    int i, len;
    if (!arrayp(dat = _races[race]) &&
        !arrayp(dat = load_race(race)))
    {
        return 0;
    }
    out = "";
    for (i = 0, len = sizeof(dat); i < len; ++i) {
        out += dat[i][random(sizeof(dat[i]))];
    }
    return out;
}

public string *
query_races()
{
    return get_files(EMP_DIR_ETC_NAMES);
}

public string **
query_token_arrays(string race)
{
    if (!arrayp(_races[race])) {
        load_race(race);
    }
    return _races[race];
}

public varargs string
set_name(object npc, string race)
{
    int gender;
    string name;
    if (!objectp(npc)) {
        npc = previous_object();
    }
    if (!npc->query_npc()) {
        return 0;
    }
    gender = npc->query_gender();
    if (!stringp(race) &&
        !stringp(race = npc->query_race()))
    {
        race = "human";
    }
    if (gender == 0 && stringp(name = query_name(race + "_neuter"))) {
        npc->set_name(name);
    } else if (gender == 1 && stringp(name = query_name(race + "_male"))) {
        npc->set_name(name);
    } else if (gender == 2 && stringp(name = query_name(race + "_female"))) {
        npc->set_name(name);
    } else if (stringp(name = query_name(race))) {
        npc->set_name(name);
    } else {
        npc->set_name(name = race);
    }
    return name;
}
