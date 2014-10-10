#include "/d/Empire/empire.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    add_event_object("rusty");
}
