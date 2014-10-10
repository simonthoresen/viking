#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("bird");
    set_name("peacock");
    add_long("It is beautiful.");
    scale_level(1, 7);
    scale_hp(50, 90);
    scale_wc(4, 7);
    set_al(13 + random(700));
    add_property("unarmed_weapon_name", "beak");
    add_property("unarmed_damage_type", 
                 ({ "blunt", "bite", "pierce", "pierce", "claw" }));
    load_chat(10, ({ "*emote flutters out its huge wings.",
		     "*emote makes funny noises.",
		     "*emote stretches out its wings in a big fan. " +
                     "What an Amazing sight!",
		     "*emote tends its feathers.",
		     "*emote stretches out." }));
    load_a_chat(40, ({ "*emote tries to hack you in the head.",
		       "*emote runs around in panic.",
		       "*emote loses some feathers falling down." }));
}
