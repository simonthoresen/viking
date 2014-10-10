#include "/d/Empire/islands/altdorf.h"

inherit ALT_C_GUARD;

static void
create() 
{
    ::create();
    set_wandering_chance(0);
    add_property("guardian");
}
