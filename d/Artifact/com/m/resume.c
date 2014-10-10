#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    object ply, wpn;
    if (!objectp(ply = this_player()) ||
        !objectp(wpn = ART_C_WEAPON->get_instance(ply)))
    {
        write("You have no physical form.\n");
        return 1;
    }
    if (!wpn->is_suspended()) {
        return notify_fail("You are not suspended.");
    }
    if (ply->query_sp() < COST_RESUME) {
        return notify_fail("Insufficient spell points (" +
                           COST_RESUME + " required).");
    }
    ply->reduce_spell_point(COST_RESUME);
    ply->move_player("X", new(ART_R_CONTROL));
    return 1;
}

public string
short_help()
{
    return "Return from suspended form.";
}
