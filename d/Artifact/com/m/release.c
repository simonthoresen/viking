#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

private object
find_item(object ply, string arg) 
{
    int i, len;
    object *arr, obj;
    arr = all_inventory(ply);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        if (!objectp(obj = arr[i])) {
            continue;
        }
        if (!obj<-I_ARMOUR && !obj<-I_WEAPON) {
            continue;
        }
        if (obj->id(arg)) {
            return obj;
        }
    }
    return 0;
}

static int
main(string arg)
{
    object ply, obj;
    ply = this_player();
    if (!stringp(arg)) {
        return notify_fail("Release what?");
    }
    if (!objectp(obj = find_item(ply, arg))) {
        return notify_fail("You have no " + arg + ".");
    }
    write("You release the powers of " + 
          maybe_add_article(obj->short(), 1) + ".\n");
    if (obj<-I_ARMOUR) {
        obj->remove(1, 1);
    } else if (obj<-I_WEAPON) {
        obj->unwield(1, 1);
    }
    obj->destroy();
    return 1;   
}

public string
short_help() 
{
    return "Release a consumed item of power.";
}
