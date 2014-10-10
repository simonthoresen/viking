#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("skeleton");
    add_long("It is tattered with dried flesh.");
    scale_level(14, 17);
    scale_hp(250, 325);
    scale_wc(28, 32);
    scale_ac(4, 7);
    set_al(-500);
    set_aggressive(1);
    setmin("stumbles in");
    setmout("stumbles");
    add_money(random(600));
    add_property("unarmed_damage_type", ({ "claw", "bite" }));
    add_property("undead");
    
    EMP_D_WEAPON->add_weapon(40);
    EMP_D_ARMOUR->add_armour(40);
}
