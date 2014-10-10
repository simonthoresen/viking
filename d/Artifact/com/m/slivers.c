#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

public int
can_see(object obj)
{
    return objectp(obj) && obj->query_type() != "atom";
}

private string
format_duration(object obj)
{
    int dur, exp, val;
    if (!objectp(obj) || !(dur = obj->query_duration())) {
        return "[   na   ]";
    }
    if ((exp = obj->query_expire_secs()) < 0) {
        obj->destroy(); /* call_out is gone */
        return "[        ]";
    }
    val = (exp * 100) / dur;
    if (val > 99) {
        val = 99;
    }
    return sprintf("[%-8s]", "########"[0..(8 * val) / 100]);
}

private string *
create_list(object wpn)
{
    string *ret;
    object *arr;
    int i, len;
    ret = ({ });
    if (!objectp(wpn) || !arrayp(arr = all_inventory(wpn))) {
        return ret;
    }
    arr = sort_array(filter_array(arr, "can_see"), "cmp_sliver");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        ret += ({ sprintf("%-27s  %10s",
                          arr[i]->query_name(),
                          format_duration(arr[i])) });
    }
    return ret;
}

static int
main(string arg)
{
    object ply;
    if (wizardp(ply = this_player()) &&
        stringp(arg) &&
        !objectp(ply = find_player(arg)))
    {
        return notify_fail("No such player.");
    }
    EMP_D_LIST->write("Sliver name                  Duration  ",
                      create_list(ART_C_WEAPON->get_instance(ply)));
    return 1;
}

static int
cmp_sliver(object lhs, object rhs)
{
    return strcmp(lhs->query_name(), rhs->query_name());
}

public string
short_help()
{
    return "List your current slivers.";
}
