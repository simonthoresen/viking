#include "/d/Empire/islands/altdorf.h"

inherit "/d/Vampire/obj/blood_potion"; 

static void
create() 
{
    ::create();
    set_name("vial");
    set_short("a large vial of blood");
    set_long("The crimson blood is contained within a large flask.");
    add_id(({ "blood", "vial of blood" }));
    add_property(({ "liquid", "fragile", "blood", "magic" }));
    set_drinker_mess("You gulp down some of the crimson blood.\n");
    set_drinking_mess(" gulps down some blood from a large vial.\n");
    set_soft_strength(0);
    set_strength(-10);
    set_heal(0);
    set_full(4);
    set_empty_container("flask");
    set_value(1500);
    set_weight(2);
}
