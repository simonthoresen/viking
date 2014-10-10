#include "/d/Empire/islands/matouci.h"

inherit EMP_I_ARMOUR;

static void 
create() 
{
    ::create();
    set_name("Might of Jormungand");
    set_short("ring of the serpent");
    set_long("This is one of the Jormungand serpent rings. It is an ancient " +
	     "relic that offers godlike might.");
    add_id(({ "ring", "ring of the serpent" }));
    add_property("wear_msg", 
		 "The might of Jormungand fills you.\n");
    add_property("remove_msg", 
		 "The might of Jormungand leaves you.\n");
    add_property(({ "artifact" }));
    set_type("ring");
    set_ac(1);
    set_weight(1);
    set_wear_modifier("str", 6);
}
