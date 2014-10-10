#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
can_cast(object obj, object ply)
{
    return objectp(obj) && obj->can_use(ply) &&
           ply->query_property(ART_P_SPELL(obj));
}

static int
cmp_spell(object lhs, object rhs)
{
    return strcmp(lhs->query_name(), rhs->query_name());
}

private string
format_cost(object ply, object obj)
{
    int cld, rdy, val;
    if (!objectp(obj) ||
        (cld = obj->query_cooldown()) <= 0 ||
        (rdy = obj->query_ready_secs(ply)) <= 0)
    {
        return sprintf("%10d", obj->query_cast_cost());
    }
    val = (rdy * 100) / cld;
    if (val > 99) {
        val = 99;
    }
    return sprintf("[%-8s]", "########"[0..(8 * val) / 100]);
}

private string *
create_list(object ply)
{
    string *ret;
    object *arr;
    int i, len;
    ret = ({ });
    arr = filter_array(ART_D_SLIVER->query_spells(), "can_cast",
                       this_object(), ply);
    arr = sort_array(arr, "cmp_spell");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        ret += ({ sprintf("%-27s  %10s",
                          capitalize(arr[i]->query_name()),
                          format_cost(ply, arr[i])) });
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
    EMP_D_LIST->write("Spell name                   Sp cost   ",
                      create_list(ply));
    return 1;
}

public string
short_help()
{
    return "List your known spells.";
}
