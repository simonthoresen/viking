#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("potion");
    set_short("a potion of heal wounds");
    set_long("This is a potion of heal wounds. It is a clear blue liquid " +
             "contained in a small flask.");
    add_id(({ "heal wounds", "potion of heal wounds" }));
    add_property(({ "liquid", "fragile", "magic" }));
    set_drinker_mess("You drink the potion of heal wounds!\n");
    set_drinking_mess(" drinks some blue liquid from a small flask.\n");
    set_strength(-5);
    set_hp_heal(100);
    set_empty_container("flask");
    set_value(1500);
    set_weight(1);
}
