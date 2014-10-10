#include "/d/Empire/islands/chaos.h"

inherit CAS_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("Chaos mage");
    set_short("a dangerous chaos mage");
    set_long("This is a dangerous-looking chaos mage. Its hands are on " + 
	     "fire, and sparks of electricity are shooting all about it.");
    add_id(({ "mage", "dangerous mage" }));
    set_race("human");
    set_level(20 + random(10));
    set_hp(1500);
    set_sp(1000);
    add_skill("prot_magic", 100);
    add_skill("prot_fire", 30);
    add_skill("prot_electricity", 30);
    load_a_chat(50, ({ store_fp(resolve_path("cast_fireball"), "main"),
		       store_fp(resolve_path("cast_lightning"), "main") }));
    EMP_D_WEAPON->add_weapon(75);
    EMP_D_ARMOUR->add_armour(75);
}
