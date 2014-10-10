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
        island->tell_island(bold("\n\n\nONYXIA TAKES A DEEP BREATH!!\n\n\n\n"));
    }
    _next_time = time() + 25;
    call_out("do_deepbreath", 3, ply);
}

public void
do_deepbreath(object ply)
{
    object env, obj;
    if (!objectp(ply) || !objectp(env = environment(ply))) {
        return;
    }
    obj = new(resolve_path("deepbreath"));
    obj->set_hitter(ply);
    obj->move(env);
}
