#include "/d/Artifact/artifact.h"

inherit ART_I_GLYPH;

private int _bonus;

static void 
create() 
{
    ::create();
    _bonus = 0;
    set_info(query_name() + " makes the artifact glow brightly.");
}

static void
setup_weapon(object wpn)
{
    ::setup_weapon(wpn);
    wpn->set_light(_bonus);
}

static void
unset_weapon(object wpn) 
{
    ::unset_weapon(wpn);
    wpn->set_light(-_bonus);
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
