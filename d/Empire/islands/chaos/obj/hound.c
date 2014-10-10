#include "/d/Empire/islands/chaos.h"

inherit CAS_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("Chaos hound");
    set_short("a ferocious chaos hound");
    set_long("This is a ferocious chaos hound with big teeth and huge " + 
	     "claws. It breaths a fiery breath.");
    add_id(({ "hound", "beast" }));
    set_race("beast");
    set_level(20 + random(10));
    set_hp(1500);
    set_wc(75);
    add_property("unarmed_damage_type", "bite");
    add_skill("prot_fire", 70);
    add_skill("resist_bite", 50);
    add_skill("resist_claw", 50);
    load_a_chat(25, ({ store_fp(resolve_path("cast_bite"), "main"),
		       store_fp(resolve_path("cast_claw"), "main") }));
}
