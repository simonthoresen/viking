#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_world_msg(bold("The demon forces of Imhotep are invading Reikland!\n"));
    set_cooldown(6 * 60 * 60);
    add_event_object("imhotep");
}
