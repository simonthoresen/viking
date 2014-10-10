#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_name("rusty");
    set_short("a ferocious RUST monster");
    set_long("This insectile monster has four legs, a strange propeller-" +
             "shaped protrusion at the end of its tail, and two long, " +
             "feathery antennae.");
    add_id(({ "monster", "rust monster" }));
    set_level(29);
    set_hp(2000);
    set_al(0);
    set_ac(15);
    set_wc(66);
    set_aggressive(1);
    set_scary(1);
    set_bored_secs(300);
    add_money(random(1500));
    add_property("vuln_fire", 100);
    add_property("vuln_cold", 100);
    add_property("vuln_electricity", 100);
    add_property("vuln_magic", 100);
    add_property("prot_acid", 100);
    add_property("unarmed_damage_type", ({ "bite", "claw" }));
    load_a_chat(50, ({ store_fp("do_whip"),
                       store_fp("do_bite"),
                       store_fp("do_spit"),  
                       store_fp("do_rust"), 
                       store_fp("do_rain") }));
    add_hook("__hit_player", store_fp("on_hit_player"));
    add_hook("__die", store_fp("on_die"));
}

static void
do_whip(object ply, object foe) 
{
    tell_room(environment(), "The rust monster lashes out with its tail.\n");
    EMP_D_CRITICAL->hit_player(this_object(), foe, 25 + random(25), "head");
}

static void
do_bite(object ply, object foe) 
{
    tell_room(environment(), "The rust monster lunges forward.\n");
    if (EMP_D_COMBAT->hit_player(this_object(), foe, 50 + random(50),
                                 "bite", 0, "jaws") > 50)
    {
        tell_object(foe, "\n\nOOOUUUCCHHH!! That hurt!!\n\n\n");
        foe->set_busy_next_round();
    }
}

static void
do_spit(object ply, object foe) 
{
    tell_object(foe, "The rust monster spits %^B_GREEN%^%^L_RED%^ACIDIC " +
                "SLIME%^END%^ at you!\n");
    tell_room(environment(), "The rust monster spits acidic slime at " + 
              foe->query_name() + ".\n", ({ foe }));
    EMP_D_COMBAT->hit_player(this_object(), foe, 25 + random(25), 
                             "Acid", 0, "slime");
}

static void
do_rust(object ply, object foe) 
{
    object env, obj, *arr;
    int len;
    if (!objectp(env = environment())) {
        return;
    }
    arr = filter_array(all_inventory(foe), "can_rust", this_object());
    if ((len = sizeof(arr)) == 0 || !objectp(obj = arr[random(len)])) {
        tell_room(env, "The rust monster lashes out with its antennae.\n");
        EMP_D_COMBAT->hit_player(this_object(), foe, 25 + random(25),
                                 "impact", 0, "antenna");
        return;
    }
    tell_object(foe, "The rust monster hits your " + obj->query_name() + 
                " with its antenna.\n");
    tell_room(env, "The rust monster hits " + foe->query_name() + "'s " + 
              obj->query_name() + " with its antenna.\n", ({ foe }));
    obj->wear_out(50 + random(50), "acid");
    heal_self(50 + random(50));
}

public int
can_rust(object obj) 
{
    return objectp(obj) && obj->query_property("metal") && !obj->query_broken();
}

static void
do_rain(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "The rust monster sprays %^B_GREEN%^%^L_RED%^ACIDIC " +
              "SLIME%^END%^ everywhere!\n");
    arr = filter_array(all_inventory(env), "isplayer", D_FILTER);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        EMP_D_COMBAT->hit_player(this_object(), arr[i], 25 + random(25), 
                                 "Acid", 0, "slime");
    }
    env->shout("Acidic slime sprays in from the #d.", 1);
}

static int
on_hit_player(int dmg, string dtype, object foe, string loc, int prot,
              int resist, int vuln, int ac, object weapon) 
{
    if (!can_rust(weapon)) {
        return 0;
    }
    weapon->wear_out(1 + random(dmg), "acid");
    heal_self(random(dmg));
    return 0;
}

static void
on_die(object corpse, object foe) 
{
    object env, obj;
    if (objectp(foe)) {
	EMP_D_ACHIEVEMENT->unlock(foe, "rust_monster");
    }
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "%^BOLD%^The rust monster dies in an orgy of " +
              "blood and gore!%^END%^\n");
    EMP_D_COMBAT->spray_blood(env, 100, ({ this_object(), corpse }));
    if (objectp(corpse)) {
        if (objectp(obj = D_TREASURE->get_unique(resolve_path("tyrfing")))) {
            obj->move(corpse);
        } else {
            EMP_D_TREASURE->add_treasure(10000, corpse);
        }
    }
}

