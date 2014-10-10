#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("squirrel");
    set_name("possum");
    add_long("It looks very nervous.");
    scale_level(3, 9);
    scale_wc(5, 9);
    add_property("unarmed_weapon_name", "paws");
    add_property("unarmed_damage_type", 
                 ({ "blunt", "claw", "claw", "bite" }));
    set_al(50 + random(40));
    load_chat(10, ({ "*emote climbs in a tree.",
                     "*emote looks around carefully.",
                     "*emote twitches around nervously." }));
    load_a_chat(40, ({ "*emote shrieks loudly.",
                       "*emote widens its eyes.",
                       "*cringe har" }));
}
