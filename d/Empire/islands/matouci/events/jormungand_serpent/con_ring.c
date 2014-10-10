#include "/d/Empire/islands/matouci.h"

inherit EMP_I_ARMOUR;

static void 
create() 
{
    ::create();
    set_name("Toughness of Jormungand");
    set_short("loop of the serpent");
    set_long("This is one of the Jormungand serpent rings. It is an ancient " +
	     "relic that offers godlike toughness.");
    add_id(({ "loop", "loop of the serpent", "ring" }));
    add_property("wear_msg", 
		 "The toughness of Jormungand fills you.\n");
    add_property("remove_msg", 
		 "The toughness of Jormungand leaves you.\n");
    add_property(({ "artifact" }));
    set_type("ring");
    set_ac(1);
    set_weight(1);
    set_wear_modifier("con", 6);
}
