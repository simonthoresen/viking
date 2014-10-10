#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("bird");
    set_race("bird");
    set_al(21 + random(150));
    add_property("flying");
    add_property("unarmed_weapon_name", "beak");
    add_property("unarmed_damage_type", 
                 ({ "blunt", "pierce", "bite", "claw" }));
    setmin("flies in");
    setmout("flies");
    scale_level(5, 10);
    load_chat(10, ({ "The bird drops a little pile.\n",
		     "*emote tends its feathers.",
		     "*sing hap" }));
    load_a_chat(40, ({ "*emote tries to hack you in the head.",
		       "*emote flies around in panic.",
		       "*emote loses some feathers falling down." }));
}
