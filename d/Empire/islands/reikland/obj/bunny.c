#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_short("bunny");
    set_race("rabbit");
    set_name("bunny");
    scale_level(1, 7);
    scale_str(1, 3);
    scale_dex(5, 12);
    scale_hp(40, 90);
    add_property("unarmed_weapon_name", "teeth");
    add_property("unarmed_damage_type",
                 ({ "blunt", "blunt", "blunt", "bite", "bite" }));
    set_al(80 + random(40));
    setmin("hops in");
    setmout("hops");
    load_chat(10, ({ "*emote chews on some grass.",
		     "*hop",
		     "*emote scratches its ears with a 'big' leg." }));
    load_a_chat(40, ({ "You hear some wild hi-pitch screams from the bunny.\n",
		       "The bunny looks terrified!\n",
		       "*panic" }));
}

