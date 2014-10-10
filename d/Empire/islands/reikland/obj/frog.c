#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("frog");
    set_name("frog");
    add_long("It is slimy.");
    scale_level(3, 9);
    scale_str(2, 5);
    scale_dex(15, 21);
    scale_hp(40, 90);
    set_al(random(300));
    setmin("jumps in");
    setmout("jumps");
    add_skill("swimming", 70);
    add_property("unarmed_weapon_name", "teeth");
    add_property("unarmed_damage_type",
                 ({ "blunt", "blunt", "blunt", "blunt", "bite" }));
    load_chat(10, ({ "*emote croaks.",
		     "*emote hops around.",
		     "*emote makes a huge bubble of its chin.",
		     "*say <CROAK!>" }));
    load_a_chat(40, ({ "You see the frog panicking.\n",
		       "The frog hops around to avoid the hits!\n",
		       "The frog jumps high in the air!" }));
}
