#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_ROOM_INVIS;

static void
create()
{
    ::create();
    set_crumb_duration(60);
}
