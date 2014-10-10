#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("clausthaler");
    set_short("a bottle of clausthaler");
    set_drinking_mess(" pours down a bottle of clausthaler.\n");
    set_drinker_mess("Ach, sehr gut.\n");
    set_strength(2);
    set_heal(3);
    set_value(10);
    set_weight(1);
    set_full(1);
    set_empty_container("keg");
    set_soft_strength(0);
    add_id(({ "beer", "bottle" }));
    add_property("hidden");
}
