#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("firebreather");
    set_short("a firebreather");
    set_long("This is a bottle filled with a steaming purple liquid.");
    set_drinking_mess(" drinks a firebreather.\n"); 
    set_drinker_mess("A shock wave runs through your body.\n");
    set_strength(20);
    set_soft_strength(0);
    set_heal(25);
    set_value(150);
    set_weight(1);
    set_full(1);
    set_empty_container("bottle");
}
