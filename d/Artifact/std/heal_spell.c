#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private string _dtype;
private int    _heal;

static void 
create() 
{
    ::create();
    _dtype = 0;
    _heal  = 0;
    set_info(query_name() + " heals the artifact.");
}

private int
calc_heal()
{
    return _heal + query_player()->query_skill("restoration") / 10;
}

static void
setup_player(object ply)
{
    ::setup_player(ply);
    if (query_room()->query_property("no_mdefence")) {
        fizzle_spell("The area prevents it.");
        return;
    }
    tell_object(ply, "You feel your wounds mending.\n");
    ply->reduce_hit_point(-calc_heal());
}

public nomask void 
set_heal(int val) 
{
    _heal = val;
}

public nomask int
query_heal()
{
    return _heal;
}
