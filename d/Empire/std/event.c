#include "/d/Empire/empire.h"

inherit EMP_I_DAEMON;

private string  _info;
private string  _player_msg;
private string  _room_msg;
private string  _nearby_msg;
private int     _nearby_range;
private string  _island_msg;
private string  _world_msg;
private string *_objects;
private int     _cooldown;
public  int     _next_time;
public  int     _last_time;
public  string  _last_ply;
public  string  _last_env;

static void
create()
{
    ::create();
    _info         = 0;
    _player_msg   = 0;
    _room_msg     = 0;
    _nearby_msg   = 0;
    _nearby_range = 3;
    _island_msg   = 0;
    _world_msg    = 0;
    _cooldown     = 0;
    _next_time    = 0;
    _last_time    = 0;
    _last_ply     = 0;
    _last_env     = 0;
    _objects      = ({ });
}

public string
query_save_file()
{
    string *arr;
    arr = explode(source_file_name(), "/");
    return EMP_DIR_VAR_EVENTS + arr[sizeof(arr) - 2];
}

public void
reset(int not_first)
{
    ::reset(not_first);
    if (not_first == 0) {
        restore_object(query_save_file());
    }
    hook("__reset", ({ not_first }));
}

public varargs int
run(object ply, object env)
{
    object *arr;
    int i, len;
    if (!objectp(ply) && !objectp(ply = this_player())) {
        return 0;
    }
    if (!objectp(env) && !objectp(env = environment(ply))) {
        return 0;
    }
    if (_next_time > time()) {
        return 0;
    }
    if (bhook("__bopen", ({ ply, env }))) {
        return 0;
    }
    _last_ply  = ply->query_real_name();
    _last_env  = source_file_name(env);
    _last_time = time();
    if (_cooldown > 0) {
        _next_time = _last_time + _cooldown;
    }
    if (interactive(ply) && !wizardp(ply)) {
        save_object(query_save_file());
    }
    arr = ({ });
    if (stringp(_player_msg)) {
        message("", _player_msg, ply);
        arr = ({ ply });
    }
    if (stringp(_room_msg)) {
        message("", format_message(_room_msg, ply), env, arr);
        arr = all_inventory(env);
    }
    if (stringp(_nearby_msg)) {
        env->tell_nearby(replace_string(format_message(_nearby_msg, ply),
                                        "ESC-", "#"), _nearby_range);
    }
    if (stringp(_island_msg)) {
        env->call_island("tell_island", format_message(_island_msg, ply), arr);
    }
    if (stringp(_world_msg)) {
	if (wizardp(ply)) {
	    message("", "[WORLD]: " + format_message(_world_msg, ply),
                    ply, arr);
	} else {
	    message("", format_message(_world_msg, ply),
                    filter_array(users(), "is_world"), arr);
	}
    }
    for (i = 0, len = sizeof(_objects); i < len; ++i) {
        make(_objects[i], env);
    }
    hook("__open", ({ ply, env }));
    return 1;
}

public void
set_info(string val)
{
    _info = val;
}

public string
query_info()
{
    return _info;
}

public void
set_player_msg(string val)
{
    _player_msg = val;
}

public string
query_player_msg()
{
    return _player_msg;
}

public void
set_room_msg(string val)
{
    _room_msg = val;
}

public string
query_room_msg()
{
    return _room_msg;
}

public void
set_nearby_msg(string val)
{
    if (stringp(val)) {
        val = replace_string(val, "#d", "ESC-d");
        val = replace_string(val, "#D", "ESC-D");
    }
    _nearby_msg = val;
}

public string
query_nearby_msg()
{
    return _nearby_msg;
}

public void
set_nearby_range(int val)
{
    _nearby_range = val;
}

public int
query_nearby_range()
{
    return _nearby_range;
}

public void
set_island_msg(string val)
{
    _island_msg = val;
}

public string
query_island_msg()
{
    return _island_msg;
}

public void
set_world_msg(string val)
{
    _world_msg = val;
}

public string
query_world_msg()
{
    return _world_msg;
}

public void
add_event_object(string val)
{
    if (stringp(val) && strlen(val) > 0 && val[0] != '/') {
        val = resolve_path(val);
    }
    _objects += ({ val });
}

public void
set_event_objects(string *val)
{
    _objects = ({ });
    map_array(val, "add_event_object");
}

public string *
query_event_objects()
{
    return _objects;
}

public void
set_cooldown(int val)
{
    _cooldown = val;
}

public int
query_cooldown()
{
    return _cooldown;
}

public void
set_next_time(int val)
{
    _next_time = val;
    save_object(query_save_file());
}

public int
query_next_time()
{
    return _next_time;
}

public int
query_last_time()
{
    return _last_time;
}

public string
query_last_ply()
{
    return _last_ply;
}

public string
query_last_env()
{
    return _last_env;
}

static int
is_world(object ply)
{
    return objectp(ply) && ply->query_level() <= ETERNAL_LAST;
}
