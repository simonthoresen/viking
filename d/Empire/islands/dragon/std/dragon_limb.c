#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_BASE;

private object _head;

static void
create() 
{
    ::create();
    _head = 0;

    add_hook("__fight_beat", store_fp("trash_room"));
    add_hook("__heart_beat", store_fp("check_head"));
    add_hook("__damage_done", store_fp("damage_head"));
    add_hook("__bdie", store_fp("prevent_death"));
    add_hook("__choose_target", store_fp("random_target"));
}

static void
trash_room(object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    map_array(all_inventory(env), "trash_foe");
}

static void
trash_foe(object foe) 
{
    if (!objectp(foe) || !living(foe) || foe->is_dragon()) {
        return;
    }
    if (interactive(foe) && foe->query_level() > ETERNAL_LAST) {
	return;
    }
    EMP_D_COMBAT->hit_player(this_object(), foe, 15 + random(15), "impact");
}

static object
random_target(object *arr) 
{
    int len;
    if (!arrayp(arr) || (len = sizeof(arr)) == 0) {
	return 0;
    }
    return arr[random(len)];
}

static void
damage_head(int dmg, string type, object foe, string loc) 
{
    if (!objectp(_head)) {
        return;
    }
    _head->hit_player(dmg, "Drain", foe);
}

static int
prevent_death(object foe) 
{
    return 1;
}

static void
check_head() 
{
    object env;
    if (objectp(_head)) {
        return;
    }
    if (objectp(env = environment())) {
        tell_room(env, query_name() + " falls dead to the ground.\n");
        make_corpse(0, 0);
    }
    destroy();
}

private string
find_direction(string next) 
{
    mapping dat;
    string *arr;
    object env;
    int i, len;
    if (!objectp(env = environment()) || 
        !mapp(dat = env->query_exit())) 
    {
        dat = ([ ]);
    }
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        if (dat[arr[i]][0] == next) {
            return arr[i];
        }
    }
    return "off";
}

public object
move_to(object next) 
{
    object prev;
    if (!objectp(next)) {
        return 0;
    }
    if (objectp(prev = environment()) && prev == next) {
        return 0;
    }
    move_player(find_direction(file_name(next)), next);
    return objectp(prev) ? prev : next;
}

public int
query_hp() 
{
    return objectp(_head) ? _head->query_hp() : 666;
}

public int
query_max_hp() 
{
    return objectp(_head) ? _head->query_max_hp() : 666;
}

public void
set_head(object val) 
{
    _head = val;
}

public object
query_head() 
{
    return _head;
}

