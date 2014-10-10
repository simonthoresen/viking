#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    switch (val / 40) {
    case 0:
        set_name("Minotaur fighter");
        add_id("fighter");
        break;
    case 1:
        set_name("Minotaur soldier");
        add_id("soldier");
        break;
    case 2:
        set_name("Minotaur champion");
        add_id("champion");
        break;
    }
    set_long("It is an incredibly strong, bull-headed man, an unnatural " +
             "offspring of man and beast. He possesses sharp horns, double " +
             "jointed legs, hooves, pointed ears, and fur.");
    add_tmp_str(11);
    EMP_D_ARMOUR->add_armour(75 + random(val), "boot");
    EMP_D_WEAPON->add_weapon(50 + val / 2, "greataxe");
}
