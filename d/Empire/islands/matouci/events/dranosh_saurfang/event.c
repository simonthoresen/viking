#include "/d/Empire/empire.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("\nReality falls away around you as a rift appears in the " +
                 "fabric of space.\n\n");
    add_event_object("saurfang");
}
