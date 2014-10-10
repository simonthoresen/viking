#include "/d/Empire/islands/artifact.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    set_short("In the guild hallway");
    set_long("In the guild hallway.");
    add_property(({ "no_teleport", "underground" }));
}
