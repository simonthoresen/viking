#include "/d/Empire/islands/matouci.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg(bold("The ground trembles beneath your feet.\n"));
    add_event_object("hound");
}
