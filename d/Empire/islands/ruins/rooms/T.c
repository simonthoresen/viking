#include "/d/Empire/islands/ruins.h"

inherit RUN_I_ROOM;

public void
spawn_runestone()
{
    int i;
    if (!objectp(RUN_D_RUINS->query_npc(RUN_C_FORNJOT))) {
        return;
    }
    call_out_unique("spawn_runestone", FORNJOT_RUNESTONE_RESPAWN_DELAY);
    if (present(RUN_C_FORNJOT_RUNESTONE)) {
        return;
    }
    new(RUN_C_FORNJOT_RUNESTONE)->move_player("X", this_object());
    for (i = sizeof(filter_array(all_inventory(), "is_guard"));
         i < FORNJOT_RUNESTONE_NUM_GUARDS; ++i)
    {
        make(RUN_C_FORNJOT_GUARD);
    }
}

static int
is_guard(object obj)
{
    return objectp(obj) && obj<-RUN_C_FORNJOT_GUARD;
}
