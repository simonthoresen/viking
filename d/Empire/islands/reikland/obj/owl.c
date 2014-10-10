#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("bird");
    set_name("owl");
    add_long("It is brown and has yellow eyes.");
    scale_level(3, 9);
    scale_hp(100, 200);
    scale_wc(14, 17);
    set_al(0);
    add_property("unarmed_weapon_name", "beak");
    add_property("unarmed_damage_type", ({ "blunt", "bite", "claw" })); 
    add_property("flying");
    setmin("flies in");
    setmout("flies");
    load_chat(10, ({ "*emote tends its feathers.",
		     "*say OHOOOOH.",
		     "*look sto #n",
		     "*say OOOH.",
		     "*say WHOOOOH." }));
    load_a_chat(40, ({ "*emote tries to hack you in the head.",
		       "*emote swushes down on you with its claws.",
		       "*emote loses some feathers falling down." }));
}
