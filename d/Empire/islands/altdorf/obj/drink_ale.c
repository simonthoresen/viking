#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("ale");
    set_short("a huge flask of cheap ale");
    set_drinking_mess(" drinks contendedly from a huge flask of ale.\n");
    set_drinker_mess("You take a large sip from the huge flask of ale.\n");
    set_strength(1);
    set_heal(1);
    set_value(75);
    set_weight(2);
    set_full(50);
    set_empty_container("flask");
    set_soft_strength(1);
    add_id(({ "flask", "ale" }));
}
