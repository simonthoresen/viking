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
    tell_room(env, bold("\n\nONYXIA LETS OUT A HORRIFYING ROAR!\n"));
    env->tell_nearby(bold("\n\nYou hear a horrifying roar from the #d.\n"), 
                     666);
    map_array(arr - ({ ply }), "fear_living");
}

static void 
fear_living(object ply) 
{
    if (!objectp(ply) || !living(ply) || ply->is_dragon()) {
        return;
    }
    ply->run_away();
    ply->set_busy_next_round(ply->query_name() + " comes to " +
                             ply->query_possessive() + " senses.\n");
}
