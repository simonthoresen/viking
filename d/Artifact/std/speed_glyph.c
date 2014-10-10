#include "/d/Artifact/artifact.h"

inherit ART_I_GLYPH;

private int _chance;
private int _bias;

static void
create()
{
    ::create();
    _chance = 0;
    _bias   = 0;
    set_info(query_name() + " grants the wielder of the artifact a " +
             "chance to perform an additional attack in combat.");
}

static void
setup_player(object ply)
{
    ::setup_player(ply);
    tell_object(ply, "You become swift.\n");
}

static void
unset_player(object ply)
{
    ::unset_player(ply);
    tell_object(ply, "You become slow.\n");
}

static void
setup_user(object ply)
{
    ::setup_user(ply);
    tell_object(ply, "You become swift.\n");
    ply->add_hook("__fight_beat", store_fp("maybe_attack"));
}

static void
unset_user(object ply)
{
    ::unset_user(ply);
    tell_object(ply, "You become slow.\n");
    ply->remove_hook("__fight_beat");
}

public void
maybe_attack(object foe)
{
    object ply, usr;
    if (random(100) > ++_bias + _chance ||
        !objectp(ply = query_player()) ||
        !objectp(usr = query_user()) ||
        usr->query_property("last_speed_attack") == time() ||
        is_suspended())
    {
        return;
    }
    _bias = 0;
    tell_object(ply, "The " + query_name() + " glyph glows brightly!\n");
    tell_object(usr, "The " + query_name() + " glyph on " +
                ply->query_name() + " glows brightly!\n");
    usr->add_property("last_speed_attack", time());
    usr->attack();
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
