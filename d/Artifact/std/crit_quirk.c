#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private int _factor;

static void 
create()
{
    ::create();
    _factor = 0;
    set_info(query_name() + " allows the artifact to inflict critical " +
             "damage in combat.");
}

static void
setup_user(object usr)
{
    ::setup_user(usr);
    usr->add_hook("__damage_dealt", store_fp("maybe_crit"));
}

static void
unset_user(object usr)
{
    ::unset_user(usr);
    usr->remove_hook("__damage_dealt");
}

public void
maybe_crit(int dmg, string dtype, object foe, string loc, object wpn)
{
    if (wpn != query_weapon()) {
        return;
    }
    dmg = (dmg * _factor) / 100;
    EMP_D_CRITICAL->damage_dealt(query_user(), foe, dmg, loc);
}

public nomask void
set_factor(int val)
{
    _factor = val;
}

public nomask int
query_factor()
{
    return _factor;
}


 
