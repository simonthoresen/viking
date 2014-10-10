#include "/d/Empire/islands/matouci.h"

inherit EMP_I_ARMOUR;

static void 
create() 
{
    ::create();
    set_name("Wits of Jormungand");
    set_short("signet of the serpent");
    set_long("This is one of the Jormungand serpent rings. It is an ancient " +
	     "relic that offers godlike wits.");
    add_id(({ "signet", "signet of the serpent", "ring" }));
    add_property("wear_msg", 
		 "The wits of Jormungand fill you.\n");
    add_property("remove_msg", 
		 "The wits of Jormungand leave you.\n");
    add_property(({ "artifact" }));
    set_type("ring");
    set_ac(1);
    set_weight(1);
    set_wear_modifier("int", 6);
}
