#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    object ply, wpn;
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
    if (!sizeof(map_array(all_inventory(ply), "show_inventory") - ({ 0 }))) {
        write(ply->query_name() + " has no containers.\n");
    }
    return 1;
}

static int
show_inventory(object obj)
{
    object *arr;
    string str;
    int i, len;
    if (!objectp(obj) ||
        !obj->query_max_weight() ||
        !stringp(str = obj->short()))
    {
        return 0;
    }
    str = capitalize(str);
    if (!obj->is_open()) {
        write(str + " (closed)\n");
        return 1;
    }
    write(str + ":\n");
    for (i = 0, len = sizeof(arr = all_inventory(obj)); i < len; ++i) {
        if (!objectp(obj = arr[i]) ||
            !stringp(str = obj->short()))
        {
            continue;
        }
        write("    " + capitalize(str) + "\n");
    }
    return 1;
}

public string
short_help()
{
    return "Show the content of your owner's containers.";
}
