#include "/d/Empire/islands/dragon.h"

inherit item I_ITEM;
inherit util EMP_I_UTIL;

private object _hitter;
private int    _duration;

static void
create() 
{
    item::create();
    util::create();
    _hitter   = 0;
    _duration = 10;

    set_name("magma");
    set_short("FIRE FIRE FIRE FIRE FIRE FIRE FIRE FIRE " +
              "FIRE FIRE FIRE FIRE FIRE FIRE FIRE FIRE");
    add_id(source_file_name());
    set_get(0);
    set_heart_beat(1);
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

static void
on_move(object from, object to) 
{
    if (objectp(from)) {
        tell_room(from, "The magma fizzles and cools to stone.\n");
	from->tell_nearby("The magma to the #d fizzles and cools " +
			  "to stone.\n", 2);
    }
    if (objectp(to)) {
        tell_room(to, "\nMAGMA ERUPTS FROM THE GROUND!\n\n");
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

static void
heart_beat() 
{
    object env;
    if (!objectp(_hitter) || 
        !objectp(env = environment()) ||
        --_duration < 0)
    {
        destroy();
        return;
    }
    map_array(all_inventory(env), "burn_player");
}

static void
burn_player(object obj) 
{
    if (!objectp(obj) || !living(obj) || obj->is_dragon()) {
        return;
    }
    if (interactive(obj) && obj->query_level() > ETERNAL_LAST) {
        tell_object(obj, "Your wizardhood protects you from the magma.\n");
	return;
    }
    if (can_fly(obj)) {
        tell_object(obj, "You are hit by balls of flying magma!\n");
    }
    EMP_D_COMBAT->hit_player(_hitter, obj, 60 + random(60), 
                             "fire", 0, "magma");
}

public void
set_hitter(object val) 
{
    _hitter = val;
}

public object
query_hitter() 
{
    return _hitter;
}

public void
set_duration(int val) 
{
    _duration = val;
}

public int
query_duration() 
{
    return _duration;
}
