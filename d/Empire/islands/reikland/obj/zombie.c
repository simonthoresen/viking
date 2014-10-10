#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("zombie");
    add_long("It is filthy and wearing raggedy clothes.");
    scale_level(17, 19);
    scale_hp(200, 280);
    scale_wc(20, 25);
    scale_ac(6, 8);
    set_aggressivity(60);
    set_al(-400-random(300));
    setmin("walks in");
    setmout("walks");
    add_property("unarmed_damage_type", ({ "claw", "bite" }));
    add_property("undead");
    add_money(random(400));

    EMP_D_WEAPON->add_weapon(75);
    EMP_D_ARMOUR->add_armour(50);
}
