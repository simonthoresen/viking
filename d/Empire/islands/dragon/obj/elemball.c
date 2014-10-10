#include "/d/Empire/islands/dragon.h"

inherit item I_ITEM;
inherit util EMP_I_UTIL;

private object _hitter;
private string _direction;
private int    _duration;
private string _type;

static void 
create() 
{
    item::create();
    util::create();
    _hitter    = 0;
    _direction = 0;
    _duration  = 10;
    _type      = ({ "fire", "cold", "electricity",
                    "acid", "magic" })[random(5)];

    set_name(_type + "-ball");
    set_short("a HUGE ball of " + _type);
    set_get(0);
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
    call_out("continue_flight", 0.1);
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && objectp(to)) {
        tell_room(from, "The " + query_name() + " flies " + _direction + ".\n");
        tell_room(to, "\nA BALL OF " + upper_case(_type) + 
                  " COMES FLYING IN!\n\n");
    }
    if (objectp(to)) {
        map_array(all_inventory(to), "burn_player");
    }
}

static void
on_destroy() 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, bold("\n\nTHE BALL OF " + upper_case(_type) + 
                        " EXPLODES!\n"));
    map_array(all_inventory(env), "burn_player");
}

public void
continue_flight() 
{
    string file;
    object prev, next;
    if (!stringp(_direction) ||
        !objectp(prev = environment()) ||
        !stringp(file = prev->query_exit(_direction)) ||
        !objectp(next = file->__bootstrap()) ||
        --_duration < 0)
    {
        destroy();
        return;
    }
    move(next);
    call_out("continue_flight", 0.1);
}

static void 
burn_player(object obj) 
{
    if (!objectp(obj) || !living(obj) || obj->is_dragon()) {
        return;
    }
    if (interactive(obj) && obj->query_level() > ETERNAL_LAST) {
        tell_object(obj, "Your wizardhood protects you from the " + 
                    _type + ".\n");
	return;
    }
    EMP_D_COMBAT->hit_player(_hitter, obj, 60 + random(60), 
                             _type, 0, query_name());
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
set_direction(string val) 
{
    _direction = val;
}

public string
query_direction() 
{
    return _direction;
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

public void
set_type(string val) 
{
    _type = val;
}

public string
query_type() 
{
    return _type;
}

