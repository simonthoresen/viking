#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("alligator");
    set_al(-200 + random(250));
    set_aggressivity(60);
    setmin("lurks in");
    setmout("lurks");
    scale_level(18, 24);
    scale_str(18, 30);
    scale_dex(13, 19);
    scale_wc(9, 15);
    add_skill("swimming", 100);
    add_property("unarmed_weapon_name", "jaws");
    add_property("unarmed_damage_type", ({ "blunt", "bite", "claw" }));
    load_chat(10, ({ "*emote watches you.",
		     "*emote lurks in the muddy waters.",
		     "*emote swims silently towards you.",
		     "*emote is." }));
    load_a_chat(40, ({ "You see the jaws of the alligator opening widely.\n",
		       "The alligator charges!\n",
		       "The alligator swims forward for attack." }));
}
