#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("cider");
    set_short("a bottle of alcoholic cider");
    set_long("The content got a fuzzy blank consistence.");
    add_id(({ "alcoholic cider", "alchocider", "bottle" }));
    set_drinking_mess(" puts a bottle of alcoholic cider to the mouth and " +
                      "drinks it.\n");
    set_drinker_mess("You put the bottle to your mouth, then rapidly pour " +
                     "it down. Gulp. Gulp.\n");
    set_strength(3);
    set_soft_strength(30);
    set_heal(40);
    set_value(320);
    set_weight(1);
    set_full(2);
    set_empty_container("bottle");
    add_property("hidden");
}
