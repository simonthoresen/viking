#include "/d/Empire/islands/dragon.h"

inherit EMP_I_OBJECT;

public void
main(object ply, object foe) 
{
    object env, *arr;
    string island;
    if (!objectp(ply) || !objectp(env = environment(ply)) ||
        !stringp(island = env->query_island()) || 
        !arrayp(arr = island->query_livings())) 
    {
	return;
    }
    island->tell_island(bold("\n\nTHE DRAGON EGGS BEGIN TO HATCH!\n"));
    map_array(arr - ({ ply }), "summon_whelp");
}

static void 
summon_whelp(object ply) 
{
    object env;
    string whelp;
    if (!objectp(ply) || 
        !objectp(env = environment(ply)) || 
        !living(ply) || 
        ply->is_dragon()) 
    {
        return;
    }
    whelp = resolve_path("whelp");
    make(whelp, env)->do_attack(ply);
    make(whelp, env)->do_attack(ply);
}
