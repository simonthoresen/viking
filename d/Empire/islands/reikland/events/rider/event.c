#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    add_hook("__open", store_fp("create_rider"));
}

static void
create_rider(object ply, object env) 
{
    object rider, mount, obj;
    rider = new(parse_path("rider"));
    mount = new(parse_path("mount"));
    obj = new(EMP_C_REINS);
    obj->move(rider);
    obj->mount(mount);
    rider->move_player(0, env);
}
