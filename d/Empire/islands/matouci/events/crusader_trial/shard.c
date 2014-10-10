#include "/d/Empire/empire.h"

inherit EMP_I_ITEM;

private int     _deaths;
private object  _killer;
private object *_active;

static void
create() 
{
    ::create();
    _deaths = 0;
    _killer = 0;
    _active = ({ });

    set_name("shard");
    set_short(0);
    set_get(NO_GET);
    set_heart_beat(1);

    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public void
heart_beat() 
{
    if (sizeof(_active - ({ 0 })) == 0) {
        destroy();
    }
}

static void
on_move(object from, object to) 
{
    object obj;
    if (!objectp(to) || !to->query_property("room")) {
        return;
    }
    tell_room(to, bold("\nThe trial of the crusader has begun!\n\n"));
    if (objectp(obj = make(resolve_path("gormok"), to))) {
        _active += ({ obj });
        obj->add_hook("__die", store_fp("gormok_die"));
    }
}

static void
on_destroy() 
{
    object env;
    if (objectp(env = bottom_room())) {
        tell_room(env, bold("\nThe trial of the crusader has ended!\n\n"));
    }
}

public void
gormok_die(object corpse, object killer) 
{
    object env, obj1, obj2;
    if (!objectp(env = bottom_room())) {
        return;
    }
    if (objectp(killer)) {
        EMP_D_ACHIEVEMENT->try_unlock(killer, "trial_of_the_crusader", 
                                      ++_deaths, 3); 
        _killer = killer;
    }
    obj1 = make(resolve_path("acidmaw"), env);
    obj2 = make(resolve_path("dreadscale"), env);
    if (objectp(obj1)) {
        _active += ({ obj1 });
        obj1->set_partner(obj2);
        obj1->add_hook("__die", store_fp("acidmaw_die"));
    }
    if (objectp(obj2)) {
        _active += ({ obj2 });
        obj2->set_partner(obj1);
        obj2->add_hook("__die", store_fp("dreadscale_die"));
    }
}

private void
try_reward(object dst) 
{
    object obj;
    if (sizeof(_active - ({ 0 })) != 1) {
        return;
    }
    if (!objectp(dst)) {
        dst = environment();
    }
    if (objectp(obj = make(resolve_path("belt")))) {
        obj->move(dst);
    } else {
        EMP_D_TREASURE->add_treasure(5000, dst);
    }
		/* No longer part of the reward.
    if (objectp(obj = D_TREASURE->get_unique(resolve_path("gloves")))) {
        obj->move(dst);
    } else {
        EMP_D_TREASURE->add_treasure(5000, dst);
    } */
}

public void
acidmaw_die(object corpse, object killer) 
{
    if (objectp(killer) && killer == _killer) {
        EMP_D_ACHIEVEMENT->try_unlock(killer, "trial_of_the_crusader", 
                                      ++_deaths, 3); 
    }
    try_reward(corpse);
}

public void
dreadscale_die(object corpse, object killer) 
{
    if (objectp(killer) && killer == _killer) {
        EMP_D_ACHIEVEMENT->try_unlock(killer, "trial_of_the_crusader", 
                                      ++_deaths, 3); 
    }
    try_reward(corpse);
}

