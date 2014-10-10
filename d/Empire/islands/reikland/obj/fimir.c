#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("fimir");
    set_name("fimir");
    add_long("He is roughly humanoid, with a great barrel-like chest, short " +
             "powerful legs ending in three-toed clawed feet, and long " +
             "sinewy arms which reach almost to the ground. He has a tail " +
             "set with a row of bony knobs and tipped with a knobbed bony " +
             "excrescence which looks much like a heavy mace.");
    scale_level(14, 20);
    scale_hp(400, 550);
    scale_str(20, 25);
    scale_dex(15, 20);
    set_aggressivity(80);
    set_al(-450);
    set_male();
    add_money(random(50));
    add_skill("resist_cold", 15);
    add_property("unarmed_damage_type", "claw");
    load_a_chat(50, ({ store_fp("tail_attack") }));
    
    EMP_D_WEAPON->add_weapon(50);
    EMP_D_ARMOUR->add_armour(50);
}

static void
tail_attack(object ply, object foe) 
{
    EMP_D_COMBAT->hit_player(ply, foe, 5 + random(query_str()),
                             "blunt", 0, "tail");
}
