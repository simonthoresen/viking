#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("A peculiar looking man falls from the sky!\n");
    add_event_object("random");
}
