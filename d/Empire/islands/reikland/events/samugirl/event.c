#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void 
create() 
{
    ::create();
    set_room_msg("A little girls comes dancing in whisteling merrily tunes.\n");
    set_nearby_msg("You hear a girls whisteling to the #d.\n");
    add_event_object("samugirl");
}
