#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("A hooded figure appears out of the shadows!\n");
    add_event_object("kashryn");
}
