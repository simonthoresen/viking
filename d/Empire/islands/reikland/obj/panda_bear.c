#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("bear");
    set_name("panda");
    add_long("You thought it was ALMOST extinct, now, here is your chance...");
    scale_level(7, 13);
    scale_wc(13, 19);
    scale_hp(250, 450);
    add_property("unarmed_weapon_name", "claws");
    add_property("unarmed_damage_type", ({ "blunt", "claw", "claw", "bite" }));
    set_al(600 + random(400));
    load_chat(10, ({ "*emote sniffs its snout into the ground.",
		     "*emote looks around carefully.",
		     "*emote tends its fur with the forearms." }));
    load_a_chat(40, ({ "*emote swings its claws.",
		       "*emote bares its teeth.",
		       "*growl" }));
}
