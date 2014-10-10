#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("bird");
    set_name("parrot");
    add_long("Is is making funny noises.");
    scale_level(1, 7);
    scale_dex(5, 11);
    scale_hp(30, 70);
    scale_wc(8, 12);
    set_al(7 + random(200));
    setmin("flies in");
    setmout("flies");
    add_property("flying");
    add_property("unarmed_weapon_name", "beak");
    add_property("unarmed_damage_type", 
                 ({ "blunt", "pierce", "pierce", "bite", "claw" }));
    load_chat(10, ({ "*emote flaps with its wings.",
                     "*say Kokolia-loo",
                     "*say RRRRRRRRRRR!",
                     "*say Eeeeeek!",
                     "*sing mock #n",
                     "*say K-K-K",
                     "*say Bwhaaaaak!" }));
    load_a_chat(40, ({ "*emote squeeks loudly!",
                       "*scream",
                       "*emote loses some feathers falling down.",
                       "*emote flaps wildly with its wings." }));
}
