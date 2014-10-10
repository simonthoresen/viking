#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_EVENT;

static void
create()
{
    ::create();
    set_player_msg("You bump into an old man.\n");
    set_room_msg("#N bumps into an old man.\n");
    add_event_object("wiseman");
}
