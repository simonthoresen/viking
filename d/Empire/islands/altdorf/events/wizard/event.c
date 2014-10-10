#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_EVENT;

static void
create()
{
    ::create();
    set_room_msg("A bearded old man appears in a puff of smoke.\n");
    add_event_object("wizard");
}
