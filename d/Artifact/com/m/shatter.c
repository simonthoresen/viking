#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    object ply, wpn, usr;
    if (!objectp(ply = this_player()) ||
        !objectp(wpn = ART_C_WEAPON->get_instance(ply)))
    {
        write("You have no physical form.\n");
        return 1;
    }
    if (objectp(usr = wpn->query_user()) &&
        objectp(usr->query_attack()))
    {
        return notify_fail("You can not shatter while fighting.");
    }
    if (ply->query_sp() < COST_SHATTER) {
        return notify_fail("Insufficient spell points (" +
                           COST_SHATTER + " required).");
    }
    ply->reduce_spell_point(COST_SHATTER);
    write("You shatter into a thousand pieces!\n");
    wpn->message_room(ply->query_name() + " shatters into a thousand " +
                      "pieces!\n", wpn);
    wpn->destroy();
    return 1;
}

public string
short_help()
{
    return "Destroy your physical form.";
}
