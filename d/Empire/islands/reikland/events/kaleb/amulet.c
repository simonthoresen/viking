#include "/d/Empire/islands/reikland.h"

inherit armour EMP_I_ARMOUR;
inherit align  EMP_I_ALIGNED;

static void
create() 
{
    armour::create();
    align::create();

    set_name("Skillstone of Akol");
    set_short("a yellow stone pendant");
    set_long("A translucent yellow stone pendant on a leather strap.");
    add_id(({ "pendant", "stone pendant", "yellow pendant",
              "yellow stone pendant", "skillstone" }));
    set_info("It grants its wearer the ability to fight with two weapons.");
    set_type("amulet");
    set_value(1222);
    set_weight(1);
    set_ac(1);
    set_min_align(ALIGN_GOOD);
    set_wear_modifier("two_weapon", 50);
    set_wear_modifier("devotion_good", 20);
    add_property("artifact");
    add_property("wear_msg", "You feel aided in battle with two weapons.\n");
    add_property("remove_msg", "Your aid in battle vanishes.\n");
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
}

static void 
on_wear(int silent, object obj) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->add_hook("__heart_beat", store_fp("maybe_heal"));
}

static void
on_remove(int silent) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__heart_beat");
}

public void
maybe_heal() 
{
    object ply, env;
    int val;
    if (random(100) > 5 ||
        !objectp(ply = query_worn_by()) ||
        !objectp(env = environment(ply)) ||
        env->query_property("no_mdefence") ||
        ply->query_hp() >= ply->query_max_hp() ||
        (val = ply->query_tmp_prop("devotion_good")) <= 0)
    {
        return;
    }
    tell_object(ply, "Your pendant warms you, soothing your wounds.\n");
    ply->reduce_hit_point(-(val / 2 + random(val / 2)));
}
