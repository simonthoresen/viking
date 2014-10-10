#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private int _shield;

static void
create()
{
    ::create();
    _shield = 0;
    set_info(query_name() + " creates a temporary damage shield " +
             "around the artifact and its wielder.");
}

private void
setup_effect(object ply)
{
    tell_object(ply, "The air around you hardens into a protective shell.\n");
    tell_room(environment(ply), "The air around " + ply->query_name() +
              " hardens into a protective shell.\n", ({ ply }));
    ply->add_hook("__hit_player", store_fp("block_damage"));
}

private void
unset_effect(object ply)
{
    tell_object(ply, "The air around you returns to normal.\n");
    tell_room(environment(ply), "The air around " + ply->query_name() +
              " returns to normal.\n", ({ ply }));
    ply->remove_hook("__hit_player");
}

static void
setup_player(object ply)
{
    ::setup_player(ply);
    setup_effect(ply);
}

static void
unset_player(object ply)
{
    ::unset_player(ply);
    unset_effect(ply);
}

static void
setup_user(object ply)
{
    ::setup_user(ply);
    setup_effect(ply);
}

static void
unset_user(object ply)
{
    ::unset_user(ply);
    unset_effect(ply);
}

public int
block_damage(int dmg, string type, object foe, string loc,
             int prot_mod, int resist_mod, int vuln_mod,
             int ac_mod, object weapon)
{
    object ply;
    int ret;
    ply = previous_object();
    if (_shield >= dmg) {
        tell_object(ply, "The air around you absorbs the damage.\n");
        tell_room(environment(ply), "The air around " + ply->query_name() +
                  " absorbs the damage.\n", ({ ply }));
        ret = -dmg;
    } else {
        tell_object(ply, "The air around you absorbs some of the damage.\n");
        tell_room(environment(ply), "The air around " + ply->query_name() +
                  " absorbs some of the damage.\n", ({ ply }));
        ret = -_shield;
    }
    if ((_shield -= dmg) <= 0) {
        destroy_later();
    }
    return ret;
}

public nomask void
set_shield(int val)
{
    _shield = val;
}

public nomask int
query_shield()
{
    return _shield;
}
