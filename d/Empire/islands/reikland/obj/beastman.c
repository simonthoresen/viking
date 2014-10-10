#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

private string
create_mutation(int idx) 
{
    switch(idx % 11) {
    case 0:
        add_property("unarmed_damage_type", ({ "slash", "bite" }));
        return "its arms have turned into tentacles";
    case 1:
        add_property("no_headchop");
        return "its head has sunk into its chest";
    case 2:
        add_property("regen");
        return "large pulsating lumps are bulging on its body";
    case 3:
        add_property("no_stun");
        return "its limbs have convulged into twice their natural size";
    case 4:
        load_a_chat(50, ({ store_fp("attack") }));
        return "it has a second pair of limbs beneath its first";
    case 5:
        return "its feet have been replaced by those of a goat";
    case 6:
        add_skill("swimming", 100);
        return "gills have formed on its neck";
    case 7:
        set_al(-666);
        return "it has horns growing from its forehead";
    case 8:
        add_skill("night_vision", 100);
        return "its eyes gleam red";
    case 9:
        set_str(query_str() * 2);
        return "it has huge talons at the end of its limbs";
    case 10:
        add_tmp_prop("ac", 5 + random(5));
        return "its skin is thick and rigid";
    case 11:
        set_aggressive(0);
        load_chat(15, ({ "*drool", "*roll", "*say NNNNG!" }));
        return "it looks dumb";
    }
}

private string *
create_mutations(int len) 
{
    string *ret;
    int i, rnd;
    ret = ({ });
    rnd = random(666);
    for (i = 0; i < len; ++i) {
        ret += ({ create_mutation(rnd + i) });
    }
    return ret;
}

static void
create() 
{
    string *arr;
    int i, len;
    ::create();
    set_name("chaos beastman");
    add_id(({ "man", "beastman", "mutant", "creature" }));
    scale_level(15, 20);
    scale_hp(300, 700);
    scale_wc(20, 25);
    scale_ac(5, 9);
    set_aggressive(1);
    set_al(-500 - random(200));
    setmin("walks growling in");
    setmout("growls, and walks");
    add_property("unarmed_damage_type", ({ "claw", "bite" }));
    add_long("This creature was once a human, but has now received foul " +
             "mutations from the gods of chaos. " + 
             capitalize(make_list(create_mutations(1 + random(5)))) + ".");
    
    EMP_D_WEAPON->add_weapon(80);
    EMP_D_ARMOUR->add_armour(80);
}

