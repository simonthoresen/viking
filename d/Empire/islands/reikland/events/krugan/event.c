#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("A strangely malformed man appears out of the shadows!\n");
    add_event_object("krugan");
}
