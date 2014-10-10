#include "/d/Empire/islands/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    object ply, wpn, usr, env;
    if (!objectp(ply = this_player()) ||
        !objectp(wpn = ART_C_WEAPON->get_instance(ply)))
    {
        write("You have no physical form.\n");
        return 1;
    }
    if (wpn->is_suspended()) {
        return notify_fail("You are already suspended.");
    }
    if (ply->query_sp() < COST_SUSPEND) {
        return notify_fail("Insufficient spell points (" +
                           COST_SUSPEND + " required).");
    }
    if (objectp(usr = wpn->query_user()) &&
        objectp(usr->query_attack()))
    {
        return notify_fail("You can not suspend while fighting.");
    }
    ply->reduce_spell_point(COST_SUSPEND);
    ply->move_player("X", ATI_ISLAND->find_map_type(ATI_MAP_SMITHY));
    return 1;
}

public string
short_help()
{
    return "Temporary return to the great anvil.";
}
