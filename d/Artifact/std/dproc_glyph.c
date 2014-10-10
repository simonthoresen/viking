#include "/d/Artifact/artifact.h"

inherit base ART_I_GLYPH;
inherit util ART_I_DAMAGE_UTIL;

private int _chance;
private int _bias;

static void
create()
{
    base::create();
    util::create();
    _chance = 0;
    _bias   = 0;

    set_damage(20);
}

public nomask string
query_info()
{
    return query_name() + " grants the artifact a chance to perform " +
           "an additional " + query_dtype() + " attack in combat.";
}

static void
setup_user(object ply)
{
    ::setup_user(ply);
    ply->add_hook("__fight_beat", store_fp("maybe_attack"));
}

static void
unset_user(object ply)
{
    ::unset_user(ply);
    ply->remove_hook("__fight_beat");
}

public void
maybe_attack(object foe)
{
    int dmg;
    object ply, usr, env;
    if (random(100) > ++_bias + _chance ||
        !objectp(foe) ||
        !objectp(ply = query_player()) ||
        !objectp(usr = query_user()) ||
        !objectp(env = query_room()) ||
        env->query_property("no_mattack") ||
        is_suspended() ||
        is_idle())
    {
        return;
    }
    _bias = 0;
    tell_object(ply, "The " + query_name() + " glyph glows brightly!\n");
    tell_object(usr, "The " + query_name() + " glyph on " +
                ply->query_name() + " glows brightly!\n");
    apply_damage(ply, usr, foe);
}

public nomask void
set_chance(int val)
{
    _chance = val;
}

public nomask int
query_chance()
{
    return _chance;
}
