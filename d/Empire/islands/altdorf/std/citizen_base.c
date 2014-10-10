#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_MONSTER;

static void
create() {
    ::create();
    add_hook("__bnotify_attack", store_fp("notify_guards"));
}

static void
notify_guards(object foe) 
{
    object env, *arr;
    if (!objectp(foe) || 
        !interactive(foe) ||
        !objectp(env = environment()) || 
        env->query_island() != ALT_ISLAND ||
        !arrayp(arr = ALT_ISLAND->find_guards())) 
    {
	return;
    }
    arr->notify_attack(this_object(), foe,
		       env->query_map_row(),
		       env->query_map_col());
}
