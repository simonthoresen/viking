#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("\nWith great effort an undead warrior digs himself out of " +
                 "the ground!\n");
    add_event_object("kaleb");
}
