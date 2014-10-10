#include "/d/Empire/empire.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("\n\nS N A P !\n\n\nIt sounds as if something just tore loose " +
                 "from its chain somewhere close by..\n");
    add_event_object("wolf");
}
