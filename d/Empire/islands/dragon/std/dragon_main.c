#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_BASE;

private int _phasing;

static void
create() 
{
    ::create();
    _phasing = 0;

    set_bored_secs(300);
    set_wandering_chance(80);
    set_wandering_time(5);
    set_wandering_hook(store_fp("follow_crumbs"));
}

static mixed
follow_crumbs() 
{
    object env;
    string str, dst;
    if (objectp(env = environment()) &&
        stringp(str = env->query_crumb()) &&
        stringp(dst = env->query_exit(str)) &&
        !dst->query_property("no_wander"))
    {
        return str; /* follow player */
    }
    return "growl men"; /* stay put */
}

public int
init_phase(int val) 
{
    object env, obj;
    if (!objectp(env = environment()) || _phasing != 0) {
        return 0;
    }
    _phasing = 1;
    obj = DON_D_DRAGON->init_phase(val);
    obj->set_hp(max(1, query_hp()));
    obj->set_max_hp(query_max_hp());
    obj->move(env);
    map_array(query_attackers(), "force_attack", this_object(), obj);
    call_out("destroy", 0);
    return 1;
}

public void
force_attack(object player, object dragon) 
{
    dragon->hit_player(0, 0, player);
}
