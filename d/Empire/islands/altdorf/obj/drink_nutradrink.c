#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("nutradrink");
    set_short("a nutradrink");
    set_long("This looks like a nutri-bar dissolved in muddy water. " +
             "It even smells like it. Gaaagghhh!");
    set_drinking_mess(" makes sorrowful sounds while drinking " +
                      "something muddy.\n");
    set_drinker_mess("Tastes very healthy. You hope. Gaaaah...\n");
    set_strength(0);
    set_soft_strength(30);
    set_heal(30);
    set_value(180);
    set_weight(1);
    set_full(1);
    set_empty_container("bottle");
}
