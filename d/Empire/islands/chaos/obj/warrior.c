#include "/d/Empire/islands/chaos.h"

inherit CAS_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("Chaos warrior");
    set_short("an infernal chaos warrior");
    set_long("This is an infernal chaos warrior. It is mostly a huge chunk " +
	     "of muscles and sinew ready to crush anyone in its path.");
    add_id(({ "warrior", "infernal warrior" }));
    set_race("human");
    set_level(20 + random(10));
    set_str(query_str() * 3);
    set_dex(query_dex() * 3);
    set_hp(1500);
    load_a_chat(25, ({ store_fp(resolve_path("cast_frenzy"), "main"),
		       store_fp(resolve_path("cast_slam"), "main") }));
    EMP_D_WEAPON->add_weapon(75, "twohanded");
    EMP_D_ARMOUR->add_armour(75);
}
