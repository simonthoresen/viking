#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void 
create() 
{
    ::create(); 
    set_room_msg("You notice an enormously large tree standing here.\n");
    set_cooldown(60 * 60);
    add_event_object("ent"); 
}

