#include "/d/Empire/islands/altdorf.h"

inherit I_FOOD;

static void
create() 
{
    ::create();
    set_name("loaf");
    set_short("a fresh loaf");
    set_long("A long and this loaf.");
    set_value(200);
    set_weight(1);
    set_strength(34);
}
