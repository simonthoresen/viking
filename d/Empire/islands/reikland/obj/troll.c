#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("troll");
    add_long("It has thick, brown hide.");
    scale_level(24, 29);
    scale_hp(900, 1200);
    scale_wc(35, 45);
    scale_ac(20, 30);
    set_aggressivity(80);
    set_al(-500);
    setmin("tramples in");
    setmout("tramples");
    add_property("unarmed_damage_type", "impact");
    add_money(random(300));
}
