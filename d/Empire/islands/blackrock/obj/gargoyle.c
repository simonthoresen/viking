#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    set_long("It is a grotesque winged statue that has come alive. Its skin " +
             "looks impenetrable.");
    add_skill("resist_slash", 100);
    add_skill("prot_bite", 100);
    add_skill("prot_claw", 100);
    add_skill("prot_cold", 100);
    add_skill("prot_electricity", 100);
    add_skill("prot_fire", 100);
    add_skill("prot_pierce", 100);
    add_property("unarmed_damage_type", "claw");
    add_property("flying");
    add_tmp_prop("ac", val / 8);
    add_hook("__hit_player", store_fp("break_weapon"));
    EMP_D_ARMOUR->add_armour(75 + random(val), "shield");
    EMP_D_WEAPON->add_weapon(50 + random(50));
}

static int
break_weapon(int dmg, string type, object foe, string loc,
             int prot, int resist, int vuln, int ac, object wpn)
{
    if (!objectp(foe)) {
        return 0;
    }
    if (objectp(wpn)) {
        wpn->wear_out(1);
    } else if (type == "bite") {
        tell_object(foe, "AAAAOUCH!! You bite into solid rock!\n");
        foe->set_busy_next_round();
    } else if (type == "blunt") {
        message("hityou", "You smash your hand against solid rock!\n", foe);
        foe->hit_player(10 + random(10), "blunt", this_object());
    } else if (type == "claw") {
        EMP_D_COMBAT->wound_player(this_object(), foe, 25);
    }
    return 0;
}
