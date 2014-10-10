#include "/d/Empire/islands/ruins.h"

inherit RUN_I_STATUE;

static void
create()
{
    ::create();
    set_player_msg("");
    set_room_msg("");
    set_npc_file(RUN_C_KARI);
}
