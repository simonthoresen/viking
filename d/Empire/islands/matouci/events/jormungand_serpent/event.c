#include "/d/Empire/islands/matouci.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_world_msg(bold("The Jormungand Serpent has appeared in Matouci!\n"));
    set_cooldown(3 * 60 * 60);
    add_event_object("serpent");
}
