#include "/d/Artifact/artifact.h"

private mapping _stat_bonuses;
private string  _stats_desc;

public nomask string desc_rank();
public nomask string query_base_name();
public nomask int    query_rank();
public nomask int    query_max_rank();
public nomask void   setup_modifier(object ply, string mod, int val);
public nomask void   unset_modifier(object ply, string mod);

static void 
create() 
{
    _stat_bonuses = ([ ]);
    _stats_desc   = 0;
}

private string
desc_stats() 
{
    string str;
    str = desc_rank();
    if (stringp(_stats_desc)) {
        str += _stats_desc;
    } else {
        str += make_list(keys(_stat_bonuses));
    }
    return str;
}

static nomask void
setup_stat_bonuses(object ply)
{
    int i, len;
    string *arr;
    tell_object(ply, "You gain " + desc_stats() + ".\n");
    for (i = 0, len = sizeof(arr = keys(_stat_bonuses)); i < len; ++i) {
        setup_modifier(ply, arr[i], _stat_bonuses[arr[i]]);
    }
}

static nomask void
unset_stat_bonuses(object ply) 
{
    int i, len;
    string *arr;
    tell_object(ply, "You loose " + desc_stats() + "\n");
    for (i = 0, len = sizeof(arr = keys(_stat_bonuses)); i < len; ++i) {
        unset_modifier(ply, arr[i]);
    }
}

public nomask void 
set_stat_bonuses(mapping val) 
{
    _stat_bonuses = val;
}

public nomask mapping 
query_stat_bonuses() 
{
    return _stat_bonuses;
}

public nomask void 
set_stat_bonus(string key, int val) 
{
    _stat_bonuses[key] = val;
}

public nomask int 
query_stat_bonus(string key) 
{
    return _stat_bonuses[key];
}

public nomask void
set_stats_desc(string val)
{
    _stats_desc = val;
}

public nomask string
query_stats_desc()
{
    return _stats_desc;
}
