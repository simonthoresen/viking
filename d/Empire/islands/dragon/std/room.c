#include "/d/Empire/islands/dragon.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    add_property("underground");
}
