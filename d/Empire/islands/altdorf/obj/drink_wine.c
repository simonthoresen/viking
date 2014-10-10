#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("wein");
    set_short("a huge keg of Wittgensteiner wein");
    set_drinking_mess(" raises a keg, and burps contendedly after having " +
                      "some.\n");
    set_drinker_mess("You put the keg to your mouth, and drink some of the " +
                     "wein. Gaaaaah.\n");
    set_strength(30);
    set_heal(45);
    set_value(600);
    set_weight(1);
    set_full(3);
    set_empty_container("keg");
    set_soft_strength(5);
    add_id(({ "wine", "keg" }));
    remove_property("fragile");
    add_property("hidden");
}
