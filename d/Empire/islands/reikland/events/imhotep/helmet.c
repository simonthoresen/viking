#include "/d/Empire/islands/reikland.h"

inherit armour  EMP_I_ARMOUR;
inherit aligned EMP_I_ALIGNED;

static void
create() 
{
    armour::create();
    aligned::create();
    set_name("Crown of Evil");
    set_short("a raven-black crown");
    set_long("A stone crown with a black, polished surface. It radiates an " +
             "aura of pure evil.");
    add_id(({ "crown", "black crown", "stone crown" }));
    set_type("helmet");
    set_value(666);
    set_weight(3);
    set_ac(1);
    set_max_align(ALIGN_EVIL);
    set_wear_modifier("devotion_evil", 10);
    set_heart_beat(1);
    add_property(({ "artifact", "evil" }));
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
    ply->add_hook("__fight_beat", store_fp("maybe_spark"));
}

static void
on_remove(int silent) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__fight_beat");
}

public void
maybe_spark(object foe) 
{
    object ply, env;
    string type;
    int dmg;
    if (!objectp(foe) ||
        !objectp(ply = previous_object()) ||
        !objectp(env = environment(ply)) ||
        env->query_property("no_mattack") ||
        random(100) > 10) 
    {
        return;
    }
    if (interactive(ply) && 
        ply->query_alignment() > foe->query_alignment()) 
    {
        return;
    }
    type = ({ "fire", "cold", "electricity", "acid", "magic"})[random(5)];
    tell_object(ply, "Sparks of " + type + " shoot from your crown!\n");
    tell_room(env, "Sparks of " + type + " shoot from " + ply->query_name() + 
              "'s crown.\n", ({ ply }));
    dmg = ply->query_tmp_prop("devotion_evil");
    EMP_D_COMBAT->hit_players(ply, ply->query_attackers(), 
                              dmg / 3 + random(dmg / 3), type, 0,
                              this_object());
}
