#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("ghoul");
    add_long("A shaky ghoul with ooze dripping from its open wounds.");
    add_id(({ "shaky ghoul" }));
    scale_level(19, 22);
    scale_hp(400, 500);
    scale_wc(25, 28);
    scale_ac(2, 3);
    set_aggressivity(70);
    set_al(-300 + random(200));
    setmin("stumbles in");
    setmout("stumbles");
    add_property("unarmed_damage_type", ({ "claw", "bite" }));
    add_property("undead");
    add_money(random(200));
    
    EMP_D_WEAPON->add_weapon(60);
    EMP_D_ARMOUR->add_armour(60);
}
