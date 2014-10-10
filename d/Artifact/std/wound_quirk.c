#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private int _chance;

static void 
create()
{
    ::create();
    _chance = 0;
    set_info(query_name() + " allows the artifact to inflict bleeding " +
             "wounds in combat.");
}

static void
setup_user(object usr)
{
    ::setup_user(usr);
    usr->add_hook("__damage_dealt", store_fp("maybe_wound"));
}

static void
unset_user(object usr)
{
    ::unset_user(usr);
    usr->remove_hook("__damage_dealt");
}

public void
maybe_wound(int dmg, string dtype, object foe, string loc, object wpn)
{
    if (random(100) > _chance || wpn != query_weapon()) {
        return;
    }
    EMP_D_COMBAT->wound_player(query_user(), foe, dmg);
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
