#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("heineken");
    set_short("a large keg of heineken");
    set_drinking_mess(" drinks a keg of Heineken, gimme some!\n");
    set_drinker_mess("Mmmmm, das schmeckt wunderbar.\n");
    set_strength(8);
    set_heal(15);
    set_value(90);
    set_weight(1);
    set_full(2);
    set_empty_container("keg");
    set_soft_strength(0);
    add_id(({ "beer", "keg" }));
    remove_property("fragile");
    add_property("hidden");
}
