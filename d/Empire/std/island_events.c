#include "/d/Empire/empire.h"

inherit EMP_I_ISLAND_BASE;

private string *_events;
private int     _event_chance;
private int     _event_time;
private int     _check_time;
private int     _check_bias;
private object  _next_ply;
private object  _next_env;
private int     _next_time;

static void 
create() 
{
    ::create();
    _events       = ({ });
    _event_chance = 10;
    _event_time   = 10 * 60;
    _check_time   = 0;
    _check_bias   = 0;
    _next_ply     = 0;
    _next_env     = 0;
    _next_time    = 0; 
    add_hook("__move_player", store_fp("trigger_event"));
    add_hook("__heart_beat", store_fp("init_event"));
}

public void 
add_event(string val) 
{
    _events += ({ val });
}

public void 
set_events(string *val) 
{
    _events = val;
}

public void 
set_events_dir(string val) 
{
    string *arr;
    int i, len;
    _events = ({ });
    for (i = 0, len = sizeof(arr = get_files(val)); i < len; ++i) {
        string file;
	file = val + arr[i] + "/";
        if (file_size(file + "event.c") < 0 ||
            file_size(file + "ENABLED") < 0) 
        {
            continue;
        }
        _events += ({ file + "event" });
    }
}

public string *
query_events() 
{
    return _events;
}

public string 
query_random_event(object ply, object env) 
{
    int len;
    if (!arrayp(_events) || (len = sizeof(_events)) == 0) {
	return 0;
    }
    return _events[random(len)];
}

public nomask void 
trigger_event(object ply, object from, object to) 
{
    if (!interactive(ply) || ply->query_level() > ETERNAL_LAST) {
        return; /* only players trigger events */
    }
    if (objectp(_next_ply) && objectp(_next_env)) {
        return; /* already triggered */
    }
    if (time() < _check_time || time() < _next_time) {
        return; /* too soon */
    }
    _check_time = time() + 1;
    _check_bias += 5;
    if (random(100) > _event_chance + _check_bias) {
        return;
    }
    _check_bias = 0;
    _next_ply = ply;
    _next_env = to;
}

public nomask void 
init_event() 
{
    string str;
    object ply, env, obj;
    if (!objectp(ply = _next_ply) || !objectp(env = _next_env)) {
        return;
    }
    _next_ply = 0;
    _next_env = 0;
    if (!present(ply, env)) {
        return;
    }
    if (objectp(ply->query_attack())) {
        return;
    }
    if (!stringp(str = query_random_event(ply, env))) {
        return;
    }
    catch(obj = str->__bootstrap());
    if (!objectp(obj)) {
        return;
    }
    if (!obj->run(ply, env)) {
        return;
    }
    _next_time = time() + _event_time;
}

public void 
set_event_chance(int val) 
{
    _event_chance = val;
}

public int 
query_event_chance() 
{
    return _event_chance;
}

public void 
set_event_time(int val) 
{
    _event_time = val;
}

public int 
query_event_time() 
{
    return _event_time;
}

public int 
query_event_check() 
{
    return _check_time;
}

public int 
query_event_next() 
{
    return _next_time;
}
