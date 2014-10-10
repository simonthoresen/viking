#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
create() 
{
    ::create();
    add_id("knight");
}

static void
init_dangerlevel(int val) 
{
    switch (val / 60) {
    case 0:
        set_name("Death knight");
        break;
    case 1:
        set_name("Death knight blackguard");
        add_id(({ "guard", "blackguard" }));
        break;
    }
    set_long("A mighty warrior animated as an undead creature by the powers " +
             "of evil.");
    set_male();
    add_tmp_str(11);
    add_tmp_dex(11);
    add_tmp_con(11);
    add_tmp_int(11);
    add_property("undead");
    load_a_chat(25, ({ 
        "You feel weak.\n",
        "You feel ready to give up.\n",
        "You feel as if you are about to die.\n",
        "\nDEATH IS UPON YOU!\n\n", 
    }));
    EMP_D_WEAPON->add_weapon(100 + random(val));
    EMP_D_ARMOUR->add_armour(25 + random(75));
    EMP_D_ARMOUR->add_armour(25 + random(75));
}
