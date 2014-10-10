#include "/d/Empire/islands/dragon.h"

inherit EMP_I_OBJECT;

public void
main(object ply, object foe) 
{
    object env, *arr;
    string island;
    int len;
    if (!objectp(ply) || !objectp(env = environment(ply)) ||
        !stringp(island = env->query_island()) || 
        !arrayp(arr = island->query_livings()) ||
        (len = sizeof(arr = filter_array(arr, "isplayer", FILTER_OB))) == 0 ||
        !objectp(foe = arr[random(len)]) ||
        !objectp(env = environment(foe)))
    {
        return;
    }
    tell_room(env, bold("\n\nONE OF THE LARGER DRAGON EGGS HATCHES!\n"));
    env->tell_nearby(bold("A large dragon egg hatches to the #d.\n"), 10);
    make(resolve_path("guard"), env)->do_attack(foe);
}
