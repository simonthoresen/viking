#include "/d/Empire/islands/ruins.h"

inherit RUN_I_STATUE;

static void
create()
{
    ::create();
    set_player_msg("");
    set_room_msg("");
    set_npc_file(RUN_C_FORNJOT);
    add_kill_req(RUN_C_AEGIR);
    add_kill_req(RUN_C_KARI);
    add_kill_req(RUN_C_LOGI);
    add_hook("__open", store_fp("init_runestone_spawn"));
}

static void
init_runestone_spawn(object player, object statue, object fornjot)
{
    call_out("spawn_runestone", FORNJOT_RUNESTONE_SPAWN_DELAY,
             RUN_ISLAND->find_all_map_type(RUN_MAP_RUNESTONE));
}

public void
spawn_runestone(int *runestones, int runestone_idx)
{
    int pos;
    if (runestone_idx >= sizeof(runestones)) {
        return;
    }
    if (!objectp(RUN_D_RUINS->query_npc(query_npc_file()))) {
        return;
    }
    runestones[runestone_idx]->spawn_runestone();
    call_out("spawn_runestone", FORNJOT_RUNESTONE_SPAWN_DELAY,
             runestones, runestone_idx + 1);
}
