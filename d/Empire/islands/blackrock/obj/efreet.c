#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string str;
    str = ({ "fireblade", "flamestrider", "cinderlord" })[val / 40];
    set_name("Efreet " + str);
    set_long("It is a giant with reddish skin and horns and body part flesh " +
             "and flame.");
    set_male();
    add_id(str);
    add_property("unarmed_damage_type", "fire");
    add_property("magic");
    add_skill("two_weapon", 100);
    add_tmp_str(11);
    add_tmp_dex(11);
    EMP_D_ARMOUR->add_armour(75 + random(val), "belt");
    EMP_D_WEAPON->add_weapon(50 + random(50), "onehanded");
    EMP_D_WEAPON->add_weapon(50 + random(50), "onehanded");
}
