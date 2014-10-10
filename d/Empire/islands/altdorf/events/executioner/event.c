#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_EVENT;

static void
create()
{
    ::create();
    set_player_msg("You bump into a very large man.\n");
    set_room_msg("#N bumps into a very large man.\n");
    add_event_object("executioner");
}
