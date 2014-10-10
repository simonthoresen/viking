#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    switch (val / 40) {
    case 0:
        set_name("ravenous ghoul");
        break;
    case 1:
        set_name("abyssal ghoul");
        break;
    case 2:
        set_name("abyssal ghoul devourer");
        add_id(({ "abyssal ghoul", "devourer" }));
        break;
    }
    set_long("A monstrous, undead human that reeks of carrion.");
    add_tmp_str(11);
    add_skill("vuln_fire", 100);
    add_property("unarmed_damage_type", "claw");
    add_property("undead");
    EMP_D_ARMOUR->add_armour(50 + random(val), "glove");
    EMP_D_WEAPON->add_weapon(25 + random(50));
}
