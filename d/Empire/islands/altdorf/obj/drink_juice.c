#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("juice");
    set_short("a bottle of juice");
    set_long("This will really be refreshing.");
    set_drinking_mess(" pours down a bottle of juice.\n");
    set_drinker_mess("This feels good!\n");
    set_strength(0);
    set_soft_strength(33);
    set_heal(32);
    set_value(200);
    set_weight(1);
    set_full(1);
    set_empty_container("bottle");
}
