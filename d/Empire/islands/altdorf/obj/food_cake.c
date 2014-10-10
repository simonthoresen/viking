#include "/d/Empire/islands/altdorf.h"

inherit I_FOOD;

static void
create() 
{
    ::create();
    set_name("cake");
    set_short("a chocolate cake");
    set_long("A really big chocolate cake. This will most certainly " +
             "taste great!");
    set_value(300);
    set_weight(1);
    set_strength(48);
}
