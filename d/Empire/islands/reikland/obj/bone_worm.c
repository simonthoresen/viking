#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("bone worm");
    add_long("It is bone-white, eyeless, and has a large maw with strong, " +
             "bone-crushing teeth.");
    scale_level(14, 20);
    scale_hp(200, 350);
    scale_wc(18, 30);
    scale_ac(4, 8);
    set_aggressive(1);
    set_al(-250);
    setmin("twirls in");
    setmout("twirls");
    add_property("unarmed_damage_type", "bite");
}
