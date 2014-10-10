#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("crocodile");
    set_al(-200 + random(250));
    set_aggressivity(60);
    setmin("lurks in");
    setmout("lurks");
    scale_level(16, 22);
    scale_str(16, 28);
    scale_dex(11, 18);
    scale_wc(7, 13);
    add_skill("swimming", 100);
    add_property("unarmed_weapon_name", "jaws");
    add_property("unarmed_damage_type", ({ "blunt", "bite", "claw" }));
    load_chat(10, ({ "*emote watches you.",
		     "*emote lurks in the muddy waters.",
		     "*emote swims silently towards you.",
		     "*emote is." }));
    load_a_chat(40, ({ "You see the jaws of the crocodile opening widely.\n",
		       "The crocodile charges!\n",
		       "The crocodile swims forward for attack." }));
}
