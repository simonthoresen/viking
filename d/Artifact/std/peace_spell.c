#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private int _max_level;

static void 
create()
{
    ::create();
    _max_level = 0;
    set_info(query_name() + " attemps to make peace with anyone attacking " +
             "the wielder of the artifact.");
}

static void
setup_user(object ply)
{
    ::setup_user(ply);
    ply->stop_fight();
    map_array(({ ply }) + ply->query_attackers(), "make_peace");
}

public void 
make_peace(object ply)
{
    object foe;
    if (!objectp(foe = ply->query_attack())) {
        return;
    }
    if (ply->query_level() > _max_level) {
        message_player(foe->query_name() + " scoffs at you.\n");
        return;
    }
    tell_object(ply, "You stop fighting " + foe->query_name() + ".\n");
    tell_object(foe, ply->query_name() + " stops fighting you.\n");
    tell_room(environment(ply), ply->query_name() + " stops fighting " +
              foe->query_name() + ".\n", ({ ply, foe }));
    foe->stop_fight();
}

public nomask int
query_max_level()
{
    return _max_level;
}

public nomask void
set_max_level(int val)
{
    _max_level = val;
}

