#include "/d/Empire/islands/dragon.h"

inherit I_DAEMON;

public  int     _next_time;
private object *_dragons;
private mapping _damage;

static void
create()
{
    ::create();
    _next_time = 0;
    _dragons   = filter_array(DON_ISLAND->query_livings(), "call_other_true",
			      FILTER_OB, "is_onyxia");
    _damage    = ([ ]);
}

public void
reset(int not_first)
{
    ::reset(not_first);
    if (!not_first) {
        restore_object(EMP_DIR_VAR + "dragond");
    }
}

public object
init_phase(int val)
{
    object obj;
    EMP_LOG("dragon", sprintf("dragon entered phase %d, damage = %O",
                              val, _damage));
    obj = new(DON_DIR_OBJ + "dragon_p" + val);
    obj->add_hook("__damage_done", store_fp("register_dmg"));
    obj->add_hook("__damage_dealt", store_fp("register_dmg"));
    obj->add_hook("__destroy", store_fp("maybe_reset"));
    obj->add_hook("__die", store_fp("reward_kill"));
    _dragons += ({ obj });
    return obj;
}

public object
create_dragon()
{
    _dragons -= ({ 0 });
    if (_next_time > time() || sizeof(_dragons) > 0) {
	return 0;
    }
    _damage = ([ ]);
    return init_phase(0);
}

public void
maybe_reset()
{
    _dragons -= ({ 0, previous_object() });
    if (sizeof(_dragons) > 0) {
	return;
    }
    call_out("reset_nest", 10);
}

public void
reset_nest()
{
    (EMP_DIR_VAR_ISLANDS + "dragon/18/53")->maybe_spawn();
}

public void
register_dmg(int dmg, string type, object foe, string loc)
{
    string name;
    if (!objectp(foe) || !interactive(foe) ||
	!stringp(name = foe->query_real_name()))
    {
	return;
    }
    if (_damage[name] == 0) {
	EMP_LOG("dragon", name + " attacked dragon");
    }
    _damage[name] = _damage[name] + dmg;
}

public void
reward_kill(object corpse, object foe)
{
    object env;
    string island;
    if (!objectp(foe) || !objectp(env = environment(previous_object()))) {
        return;
    }
    EMP_LOG("dragon", sprintf("dragon killed, damage = %O", _damage));
    if (stringp(island = env->query_island())) {
        island->tell_island(bold("\n\nONYXIA HAS FALLEN!\n\n\n"));
    }
    _next_time = time() + 30 * 24 * 60 * 60;
    save_object(EMP_DIR_VAR + "dragond");
    map_array(({ foe->query_real_name() }) | keys(_damage), "reward_killer");
    if (!objectp(corpse)) {
        corpse = env;
    }
    make(DON_DIR_OBJ + "dragon_egg", corpse);
    make(DON_DIR_OBJ + "dragonhide", corpse);
    make(DON_DIR_OBJ + "dragonhide", corpse);
    make(DON_DIR_OBJ + "treasure", corpse);
}

static void
reward_killer(string name)
{
    object ply;
    if (!objectp(ply = find_player(name))) {
        return;
    }
    if (_damage[name] < 1000) {
	EMP_LOG("dragon", name + " NOT rewarded");
	tell_object(ply, "You have not contributed enough to earn a reward.\n");
	return;
    }
    EMP_LOG("dragon", name + " rewarded");
    make(DON_C_BLOOD, ply);
    ply->add_exp(5 * 1000000);
    EMP_D_ACHIEVEMENT->unlock(ply, "lair_of_onyxia");
}

public int
query_next_time()
{
    return _next_time;
}

public object *
query_dragons()
{
    return _dragons;
}

public mapping
query_damage()
{
    return _damage;
}
