#include "/d/Empire/islands/matouci.h"

inherit EMP_I_ARMOUR;

static void
create() 
{
    ::create();
    set_name("Protection of Jormungand");
    set_short("amulet of the serpent");
    set_long("This is the amulet of the Jormungand serpent. It is an ancient " +
	     "relic that offers godlike protection.");
    add_id(({ "amulet", "amulet of the serpent" }));
    add_property("wear_msg", 
		 "The protection of Jormungand fills you.\n");
    add_property("remove_msg", 
		 "The protection of Jormungand leaves you.\n");
    add_property(({ "artifact" }));
    set_type("amulet");
    set_ac(1);
    set_weight(1);
    set_wear_modifier("resist_acid", 30, 100);
    set_wear_modifier("resist_bite", 30, 100);
    set_wear_modifier("resist_blunt", 30, 100);
    set_wear_modifier("resist_chop", 30, 100);
    set_wear_modifier("resist_claw", 30, 100);
    set_wear_modifier("resist_cold", 30, 100);
    set_wear_modifier("resist_drain", 30, 100);
    set_wear_modifier("resist_electricity", 30, 100);
    set_wear_modifier("resist_fire", 30, 100);
    set_wear_modifier("resist_impact", 30, 100);
    set_wear_modifier("resist_magic", 30, 100);
    set_wear_modifier("resist_pierce", 30, 100);
    set_wear_modifier("resist_slash", 30, 100);
}

