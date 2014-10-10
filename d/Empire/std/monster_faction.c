#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER_EXP;

private string _faction;

static void
create() 
{
    ::create();
    _faction = 0;
}

public void
create_done()
{
    ::create_done();
    if (!stringp(_faction)) {
        return;
    }
    add_hook("__move", store_fp("help_request"));
    add_hook("__bnotify_attack", store_fp("request_help"));
}

static nomask void 
help_request(object from, object to) 
{
    object *arr;
    int i, len;
    if (!objectp(to)) {
        return; 
    }
    arr = all_inventory(to) - ({ this_object(), 0 });
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        object foe;
        if (objectp(foe = arr[i]->query_attack()) &&
            arr[i]->query_faction() == _faction)
        {
            do_attack(foe);
            break;
        }
    }
}

static nomask void
request_help(object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = bottom_room())) {
        return;
    }
    arr = all_inventory(env) - ({ this_object(), 0 });
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        object ply;
        if (objectp(ply = arr[i]) && !objectp(ply->query_attack()) &&
            ply->query_faction() == _faction)
        {
            ply->do_attack(foe);
        }
    }
}

public nomask void
set_faction(string val) 
{
    if (is_create_done()) {
        error("set_faction() must be called in create()");
    }
    _faction = val;
}

public nomask string
query_faction() 
{
    return _faction;
}

