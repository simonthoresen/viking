#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    add_hook("__open", store_fp("create_rider"));
}

private object
create_mob() 
{
    string *arr, str;
    object obj;
    int len;
    arr = get_files("/room/monster/*.c");
    if ((len = sizeof(arr)) == 0) {
        return 0;
    }
    str = arr[random(len)];
    str = str[0..strlen(str) - 3];
    if (!objectp(obj = new("/room/monster/" + str))) {
        return 0;
    }
    obj->set_short(lower_case(obj->short()));
    return obj;
}

static void
create_rider(object ply, object env) 
{
    object rider, mount, obj;
    if (!objectp(rider = create_mob()) ||
        !objectp(mount = create_mob()))
    {
        return;
    }
    if (!objectp(obj = D_TREASURE->get_unique(resolve_path("ureins")))) {
        obj = new(resolve_path("reins"));
    }
    obj->move(rider);
    obj->mount(mount);
    rider->move_player(0, env);
}
