#include "/d/Empire/empire.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_player_msg("You step in some sort of slimy puddle..\n");
    set_room_msg("#N steps in some sort of slimy puddle..\n");
    add_event_object("slime");
}
