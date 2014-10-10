#include "/d/Empire/islands/reikland.h"
#define P_MAGIC ("fimir_magic")

inherit EMP_I_DAEMON;

public void
enchant_weapon(object obj) 
{
    if (!objectp(obj) || !obj->query_property("weapon")) {
        return;
    }
    if (!arrayp(obj->query_hook("__weapon_hit"))) {
        obj->add_hook("__weapon_hit", store_fp("maybe_spark"));
    }
    obj->add_property(P_MAGIC, obj->query_property(P_MAGIC) + 2);
    obj->add_property("magic");
}

public void
maybe_spark(object foe) 
{
    object obj, ply, env;
    string type, desc;
    int val, idx;
    if (!objectp(foe) ||
        !objectp(obj = previous_object()) || 
        !objectp(ply = obj->query_wield()) ||
        !objectp(env = environment(ply)) ||
        env->query_property("no_mattack"))
    {
        return;
    }
    val = obj->query_property(P_MAGIC);
    if (random(100) > (50 * val) / (val + 10)) {
        return; // approaches 50% with property 100, never exceeding
    }
    idx  = random(6);
    type = ({ "fire", "cold", "electricity", "drain", "acid", "magic"})[idx];
    desc = ({ "blazing flames", "freezing ice-shards", "blinding lightning",
	      "vampiric magic", "scorching acid", "foul magic"})[idx];
    tell_object(ply, "Your " + obj->query_name() + " shoots " + desc + "!\n");
    tell_room(env, ply->query_name() + "'s " + obj->query_name() + " shoots " +
              desc + ".\n", ({ ply }));
    EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), type, 0, obj);
}
