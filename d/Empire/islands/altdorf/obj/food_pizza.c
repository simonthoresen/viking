#include "/d/Empire/islands/altdorf.h"

inherit I_FOOD;

static void
create() 
{
    ::create();
    set_name("pizza");
    set_short("a pizza Margherita");
    set_long("A pizza Margherita. It looks like it's enought to feed an " +
             "starving adventurer.");
    add_id("margherita");
    set_value(320);
    set_weight(1);
    set_strength(40);
    set_eater_mess("You feel full after eating that pizza.\n");
}
