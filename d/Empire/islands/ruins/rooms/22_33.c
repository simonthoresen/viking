#include "/d/Empire/islands/ruins.h"

inherit RUN_I_ROOM;

static void
create()
{
    ::create();
    add_property("no_wander");
}
