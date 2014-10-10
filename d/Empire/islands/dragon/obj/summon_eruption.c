#include "/d/Empire/islands/dragon.h"

inherit EMP_I_OBJECT;

private int _next_time;

static void
create() 
{
    ::create();
    _next_time = 0;
}

public void
main(object ply, object foe) 
{
    object env;
    string island;
    if (!objectp(ply) || !objectp(foe) || time() < _next_time) {
        return;
    }
    if (objectp(env = environment(ply)) &&
        stringp(island = env->query_island())) 
    {
        island->tell_island(bold("\n\nTHE GROUND BEGINS TO TREMBLE!\n\n\n"));
    }
    _next_time = time() + 25;
    call_out("do_eruption", 1, ply);
}

public void
do_eruption(object ply) 
{
    object env, *arr;
    string island;
    if (!objectp(ply) || !objectp(env = environment(ply)) ||
        !stringp(island = env->query_island()) ||
        !arrayp(arr = island->query_livings()))
    {
        return;
    }
    map_array(arr - ({ ply }), "summon_eruption", this_object(), ply);
}

public void
summon_eruption(object victim, object hitter) 
{
    object env, obj;
    if (!objectp(victim) || 
        !objectp(hitter) ||
        !objectp(env = environment(victim)) ||
        objectp(present(DON_C_ERUPTION, env))) 
    {
        return;
    }
    obj = new(DON_C_ERUPTION);
    obj->set_hitter(hitter);
    obj->move(env);
}
