#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string str;
    str = ({ "necromancer", "remnant", "soulreaver" })[val / 40];
    set_name("Lich " + str);
    set_long("It is an undead human skeleton eminating an aura of magic.");
    add_id(str);
    add_property("unarmed_damage_type", "claw");
    add_property("undead");
    load_a_chat(10 + val / 10, ({ 
                store_fp(resolve_path("cast_raise_dead"), "main") }));
    EMP_D_ARMOUR->add_armour(50 + random(val), "ring");
    EMP_D_WEAPON->add_weapon(50 + random(50), "onehanded");
}
