#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("potion");
    set_short("a potion of healing");
    set_long("The potion is contained in a large flask. It is a light " +
             "blue liquid that looks very delicious.");
    add_id(({ "healing", "healing potion", "potion of healing" }));
    add_property(({ "liquid", "fragile", "magic" }));
    set_drinker_mess("You take a sip of the healing potion.\n");
    set_drinking_mess(" takes a sip from a large flask.\n");
    set_heal(200);
    set_full(4);
    set_empty_container("flask");
    set_value(18000);
    set_weight(2);
}
