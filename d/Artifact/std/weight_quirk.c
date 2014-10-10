#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private int _bonus;

static void 
create() 
{
    ::create();
    _bonus = 0;
}

public nomask string
query_info()
{
    return query_name() + " " + (_bonus < 0 ? "reduces" : "increases") +
           " the weight of the artifact.";
}

static void
setup_weapon(object wpn)
{
    ::setup_weapon(wpn);
    wpn->set_weight(wpn->query_weight() - _bonus);
}

static void
unset_weapon(object wpn) 
{
    ::unset_weapon(wpn);
    wpn->set_weight(wpn->query_weight() + _bonus);
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
