#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("racoon");
    set_name("racoon");
    add_long("It has a broad tail.");
    scale_level(4, 10);
    scale_wc(11, 14);
    scale_hp(80, 150);
    set_al(-18 + random(90));
    add_property("unarmed_weapon_name", "claws");
    add_property("unarmed_damage_type",
                 ({ "blunt", "claw", "claw", "claw", "bite" }));
    load_chat(10, ({ "*emote sniffs its snout into the ground.",
                     "*emote looks around carefully.",
                     "*emote tends its fur with the forearms." }));
    load_a_chat(40, ({ "*emote swings its tail.",
                       "*emote reveals a set of claws!",
                       "*sneer" }));
}
