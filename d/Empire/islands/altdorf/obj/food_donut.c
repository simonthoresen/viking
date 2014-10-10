#include "/d/Empire/islands/altdorf.h"

inherit I_FOOD;

static void
create() 
{
    ::create();
    set_name("donut");
    set_short("a donut");
    set_long("A tasty looking donut.");
    set_value(110);
    set_weight(1);
    set_strength(19);
}
