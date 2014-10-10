#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("wolf");
    set_name("wolf");
    add_long("It has gray fur and sharp teeth.");
    scale_level(16, 20);
    scale_hp(275, 350);
    scale_wc(20, 30);
    scale_ac(3, 7);
    set_aggressive(1);
    set_al(-50);
    setmin("wanders in");
    setmout("wanders");
    add_property("unarmed_damage_type", ({ "bite", "claw" }));
}
