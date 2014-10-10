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
    _duration = 5;

    set_name("napalm");
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
        tell_room(from, "The napalm dies away.\n");
	from->tell_nearby("The napalm to the #d dies away.\n", 1);
    }
    if (objectp(to)) {
        tell_room(to, "\nBURNING NAPALM FLOODS THE ROOM!\n\n");
        catch(map_array(all_inventory(to), "burn_player"));
        call_out("flood_exits", 0.1);
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
    catch(map_array(all_inventory(env), "burn_player"));
}

static void
burn_player(object obj)
{
    int dmg;
    if (!objectp(obj) || !living(obj) || obj->is_dragon()) {
        return;
    }
    if (interactive(obj) && obj->query_level() > ETERNAL_LAST) {
        tell_object(obj, "Your wizardhood protects you from the napalm.\n");
	return;
    }
    dmg = 175;
    if (can_fly(obj)) {
        tell_object(obj, "You avoid some of the burning napalm.\n");
        dmg /= 2;
    }
    EMP_D_COMBAT->hit_player(_hitter, obj, dmg + random(dmg), 
                             "fire", 0, "napalm");
}

public void 
flood_exits()
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    catch(map_array(env->query_commands(), "flood_room"));
}

static void
flood_room(string cmd) 
{
    object env, obj;
    string dst;
    if (_duration <= 0 ||
        !objectp(env = environment()) ||
        !stringp(dst = env->query_exit(cmd)) ||
        !objectp(env = dst->__bootstrap()) ||
        objectp(present(DON_C_DEEPBREATH, env)))
    {
        return;
    }
    obj = new(DON_C_DEEPBREATH);
    obj->set_duration(_duration - 1);
    obj->set_hitter(_hitter);
    obj->move(env);
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
