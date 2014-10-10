#include "/d/Artifact/artifact.h"

inherit ART_I_GLYPH;

private int _bonus;

static void 
create() 
{
    ::create();
    _bonus = 0;
    set_info(query_name() + " increases the weapon class of the artifact.");
}

static void
setup_player(object ply)
{
    ::setup_player(ply);
    tell_object(ply, "You become capable of inflicting more damage.\n");
}

static void
unset_player(object ply)
{
    ::unset_player(ply);
    tell_object(ply, "You become less capable of inflicting damage.\n");
}

static void
setup_weapon(object wpn)
{
    ::setup_weapon(wpn);
    wpn->add_hook("__weapon_hit", store_fp("increase_wc"));
}

static void
unset_weapon(object wpn) 
{
    ::unset_weapon(wpn);
    wpn->remove_hook("__weapon_hit");
}

public int
increase_wc(object foe)
{
    return _bonus;
}

public nomask void 
set_bonus(int val) 
{
    _bonus = val;
}

public nomask int
query_bonus()
{
    return _bonus;
}
