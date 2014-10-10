#include "/d/Empire/islands/reikland.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_race("demon");
    set_no_corpse(1);
    setmin("flies in");
    setmout("flies");
    add_property("unarmed_damage_type", "claw");
    add_property("flying");
    add_property("evil");
    add_skill("resist_cold", 100);
    add_skill("prot_magic", 50);
    add_skill("two_weapon", 100);
    add_hook("__die", store_fp("count_death"));
    add_hook("__init", store_fp("attack_good"));
    add_hook("__hit_player", store_fp("modify_damage"));
    add_hook("__bnotify_attack", store_fp("scare_mortals"));
}

static int
is_evil(object obj) 
{
    if (!objectp(obj)) {
        return 0;
    }
    return obj->query_alignment() < ALIGN_EVIL ||
           obj->query_tmp_prop("evil") || 
           obj->query_property("evil");
}

static int
is_good(object obj) 
{
    if (!objectp(obj)) {
        return 0;
    }
    return obj->query_alignment() > ALIGN_SAINTLY ||
           obj->query_tmp_prop("good") || 
           obj->query_property("good");
}

static void
count_death(object corpse, object killer) 
{
    EMP_D_ACHIEVEMENT->add_unlock(killer, "demon_slayer", 1, 100);
}

static void
attack_good() 
{
    object ply;
    if (!objectp(ply = this_player()) || 
        ply->query_invis() || 
        is_evil(ply)) 
    {
        return;
    }
    do_attack(ply);
}

static int
modify_damage(int dmg, string type, object foe, string loc, 
              int prot, int resist, int vuln, int ac, object wpn) 
{
    object env;
    if (!objectp(env = environment())) {
        return 0;
    }
    if (lower_case(type) == "fire") {
        tell_room(env, "The demon does not seem to be affected by the fire.\n");
        heal_self(dmg / 2);
        return -dmg;
    }
    if (is_evil(wpn)) {
        return -dmg / 2;
    }
    if (dmg > 30) {
        command("scream ago");
    }
    if (resist < -10) {
        command("cackle");
    }
    if (prot < -20) {
        command("hydr ehv");
    }
    if (dmg < 10 && random(100) > 25) {
        return 0;
    }
    if (is_good(wpn)) {
        tell_object(foe, "Your " + wpn->query_name() + " rips straight " +
                    "through the demon's skin!\n");
        return 2 * dmg;
    } 
    if (is_good(foe)) {
        tell_object(foe, "You rip straight through the demon's skin.\n");
        return dmg;
    }
    return 0;
}

static int 
scare_mortals(object foe) 
{
    if (!interactive(foe) || 
        foe->query_level() >= ETERNAL_FIRST) 
    {
        return 0;
    }
    command("say BOO!");
    foe->run_away();
    return 1;
}
