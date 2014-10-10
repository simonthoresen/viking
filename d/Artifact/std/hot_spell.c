#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private string _dtype;
private int    _heal;

static void 
create() 
{
    ::create();
    _dtype = 0;
    _heal  = 0;
    set_info(query_name() + " heals the artifact and " +
             "its wielder over a period of time.");
}

public void
apply_heal()
{
    object ply, env;
    if (!objectp(ply = previous_object()) ||
        !objectp(env = environment(ply)) ||
        env->query_property("no_mdefence"))
    {
        return;
    }
    tell_object(ply, "You feel your wounds mending.\n");
    ply->reduce_hit_point(-_heal);
}

static void
setup_player(object ply)
{
    ::setup_player(ply);
    ply->add_hook("__heart_beat", store_fp("apply_heal"));
}

static void
unset_player(object ply)
{
    ::unset_player(ply);
    ply->remove_hook("__heart_beat");
}

static void
setup_user(object ply)
{
    ::setup_user(ply);
    ply->add_hook("__heart_beat", store_fp("apply_heal"));
}

static void
unset_user(object ply)
{
    ::unset_user(ply);
    ply->remove_hook("__heart_beat");
}

public nomask void 
set_heal(int val) 
{
    _heal = val;
}

public nomask int
query_heal()
{
    return _heal;
}
