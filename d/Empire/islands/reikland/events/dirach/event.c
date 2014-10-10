#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("A crazed fimir magician appears in a puff of lightning!\n");
    add_event_object("dirach");
}
