#include "/d/Artifact/artifact.h"

inherit EMP_I_COMMAND;

static int
main(string arg)
{
    object ply, wpn, *arr;
    if (!objectp(wpn = ART_C_WEAPON->get_instance(this_player())) ||
        wpn->is_suspended())
    {
        write("You have no physical form.\n");
        return 1;
    }
    if (!objectp(ply = wpn->query_owner())) {
        write("You have no owner.\n");
        return 1;
    }
    arr = filter_array(all_inventory(ply), "can_see");
    if (stringp(arg)) {
        if (find_first('s', arg) >= 0) {
            arr = sort_array(arr, "cmp_desc");
        }
        if (find_first('t', arg) >= 0) {
            arr = filter_array(arr, "is_tagged");
        }
        if (find_first('u', arg) >= 0) {
            arr = filter_array(arr, "is_not_tagged");
        }
    }
    map_array(arr, "write_desc");
    return 1;
}

static int
can_see(object obj)
{
    return objectp(obj) && stringp(obj->short());
}

static int
cmp_desc(object lhs, object rhs)
{
    return strcmp(lhs->short(), rhs->short());
}

static int
is_tagged(object obj)
{
    return obj->query_property("tagged");
}

static int
is_not_tagged(object obj)
{
    return !obj->query_property("tagged");
}

static void
write_desc(object obj)
{
    write((obj->query_property("tagged") ? "*" : " ") +
          capitalize(obj->short()) + "\n");
}

public string *
query_action()
{
    return ({ "i", "inventory" });
}

public string
short_help()
{
    return "Show the inventory of your owner.";
}
