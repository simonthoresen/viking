#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("potion");
    set_short("a potion of mind restore");
    set_long("The potion of mind restore is contained in a small flask. " +
             "It is a light violet liquid that looks very delicious.");
    add_id(({ "mind restore", "potion of mind restore" }));
    add_property(({ "liquid", "fragile", "magic" }));
    set_drinker_mess("You drink the potion of mind restore! Ahh!\n");
    set_drinking_mess(" drinks some violet liquid from a small flask.\n");
    set_soft_strength(-5);
    set_strength(-5);
    set_sp_heal(200);
    set_empty_container("flask");
    set_value(3000);
    set_weight(1);
}
