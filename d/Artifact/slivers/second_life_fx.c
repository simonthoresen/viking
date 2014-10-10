#include "/d/Artifact/artifact.h"

inherit ART_I_EFFECT;

static void
setup_player(object ply) 
{
    ::setup_player(ply);
    ply->add_hook("__bdie", store_fp("on_bdie"));
    destroy(30); // invuln for 30 seconds
}

static void
unset_player(object ply) 
{
    ::unset_player(ply);
    ply->remove_hook("__bdie");
}

public int
on_bdie(object foe) 
{
    return 1;
}
