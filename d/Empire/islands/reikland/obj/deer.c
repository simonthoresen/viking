#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("deer");
    set_name("deer");
    add_long("It is grassing calmly.");
    scale_level(8, 17);
    scale_wc(15, 25);
    scale_hp(500, 700);
    set_al(40 + random(300));
    add_property("unarmed_weapon_name", "hooves");
    add_property("unarmed_damage_type", 
                 ({ "blunt", "blunt", "blunt", "blunt", "bite" }));
    load_chat(10, ({ "*emote grasses from some bushes.\n",
		     "*emote stretches out and scans around for a very short " +
                     "period of time.",
		     "*emote walks around a little." }));
    load_a_chat(40, ({ "The deer swings out with its hooves.\n",
                       "The deer tries to ram with its crown.\n",
		       "*snort" }));
}
