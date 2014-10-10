#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("squirrel");
    set_name("squirrel");
    add_long("It is trying to hide.");
    scale_level(2, 10);
    scale_dex(10, 13);
    scale_wc(10, 16);
    scale_hp(80, 150);
    set_al(27 + random(130));
    add_property("unarmed_weapon_name", "claws");
    add_property("unarmed_damage_type", 
                 ({ "blunt", "blunt", "claw", "claw", "bite" }));
    load_chat(10, ({ "*emote jumps from tree to tree.",
		     "*emote looks around carefully.",
		     "*emote tends its fur with the forearms." }));
    load_a_chat(40, ({ "*sneer", 
                       "*emote stands on its two legs.",
		       "*jump mad" }));
}
