#include "/d/Empire/islands/chaos.h"

inherit EMP_I_EVENT;

static void
create()
{
    ::create();
    set_world_msg(bold("The forces of chaos are invading Altdorf!\n"));
    set_cooldown(6 * 60 * 60);
    add_event_object(CAS_DIR_OBJ + "portal");
}
