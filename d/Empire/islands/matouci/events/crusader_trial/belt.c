#include "/d/Empire/empire.h"

inherit I_ARMOUR;

static void
create() 
{
    ::create();
    set_type("belt");
    set_name("Belt of the Crusader");
    set_short("a plated leather belt");
    set_long("A heavy lether belt inset with steel plates.");
    add_id(({ "belt", "plated belt", "leather belt" }));
    set_ac(0);
    set_weight(3);
    set_value(2222);
    add_property("wear_msg", "You feel very protected wearing the belt.\n");
    add_property("remove_msg", "You feel vulnerable removing the belt.\n");
    add_property(({ "tagged", "steel", "leather" }));
		add_property("protected", 100);
    set_wear_modifier("ac", 4, 4);
    set_wear_modifier("con", 2, 2);
}
