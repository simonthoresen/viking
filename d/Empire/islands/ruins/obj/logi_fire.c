#include "/d/Empire/islands/ruins.h"

inherit EMP_I_ITEM;

private int    _amount;
private int    _expire;
private object _hitter;

static void
create()
{
    ::create();
    _amount = 1;
    _expire = time() + LOGI_FIRE_DURATION_SECS;
    _hitter = 0;

    set_name("liquid fire");
    set_long("It is a sticky liquid which is on fire.");
    add_id("fire");
    add_id(source_file_name());
    add_property("fire");
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (!objectp(env) || !living(env)) {
        return;
    }
    tell_object(env, "\n%^B_YELLOW%^%^RED%^YOU CATCH FIRE!!%^END%^\n\n");
    env->add_hook("__heart_beat", store_fp("apply_fire"));
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    if (!objectp(env) || !living(env)) {
        return;
    }
    tell_object(env, "You are no longer on fire!\n");
    env->remove_hook("__heart_beat");
}

public void
apply_fire()
{
    object ply;
    if (!objectp(_hitter) ||
        !objectp(ply = environment()) ||
        ply->query_dead() ||
        _expire < time())
    {
        destroy_later();
        return;
    }
    EMP_D_COMBAT->hit_player(_hitter, previous_object(),
                             _amount / 2 + random(_amount / 2), "fire");
}

public void
add_amount(int val)
{
    _expire = time() + LOGI_FIRE_DURATION_SECS;
    _amount += val;
}

public int
query_amount()
{
    return _amount;
}

public void
set_hitter(object val)
{
    _hitter = val;
}

public object
query_hitter()
{
    return _hitter;
}
