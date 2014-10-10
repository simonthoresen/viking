#include "/d/Empire/empire.h"
#define P_SCARED(who) ("scared_by_" + (who))

inherit EMP_I_MONSTER_RESPONSE;

private string _scary_id;

static void
create() 
{
    ::create();
    _scary_id = 0;
}

public void
create_done()
{
    ::create_done();
    if (!stringp(_scary_id)) {
        return;
    }
    add_hook("__bnotify_attack", store_fp("disable_warn"));
    add_hook("__battack", store_fp("warn_player"));
}

static nomask int
try_warn(object foe) 
{
    if (!stringp(_scary_id) ||
        foe->query_npc() ||
        foe->query_wimpy() == 0 ||
        foe->query_tmp_prop(P_SCARED(_scary_id)))
    {
        return 0;
    }
    foe->add_tmp_prop(P_SCARED(_scary_id), 1);
    return 1;
}

static nomask int
warn_player(object foe) 
{
    if (!try_warn(foe)) {
        return 0;
    }
    foe->run_away();
    return 1;
}

static nomask void
disable_warn(object foe) 
{
    try_warn(foe);
}

public nomask void
set_scary_id(string val) 
{
    if (is_create_done()) {
        error("set_scary_id() must be called in create()");
    }
    _scary_id = val;
}

public nomask string
query_scary_id() 
{
    return _scary_id;
}

public nomask void
set_scary(int val)
{
    set_scary_id(val ? source_file_name() : 0);
}

public nomask int
is_scary()
{
    return stringp(_scary_id);
}
