#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER_LOGGER;

private string _create_msg;
private string _destroy_msg;
private string _die_msg;
private string _kill_msg;

static void
create()
{
    ::create();
    _create_msg  = 0;
    _destroy_msg = 0;
    _die_msg     = 0;
    _kill_msg    = 0;
}

public void
create_done()
{
    ::create_done();
    if (stringp(_create_msg)) {
        add_hook("__move", store_fp("echo_create_msg"));
    }
    if (stringp(_destroy_msg)) {
        add_hook("__destroy", store_fp("echo_destroy_msg"));
    }
    if (stringp(_die_msg)) {
        add_hook("__die", store_fp("echo_die_msg"));
    }
    if (stringp(_kill_msg)) {
        add_hook("__kill", store_fp("echo_kill_msg"));
    }
}

static void
echo_create_msg(object from, object to)
{
    if (objectp(from) || !objectp(to)) {
        return;
    }
    tell_room(to, format_message(_create_msg, this_object()));
}

static void
echo_destroy_msg()
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, format_message(_destroy_msg, this_object()));
}

static void
echo_die_msg(object corpse, object killer)
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, format_message(_destroy_msg, this_object(), killer));
}

static void
echo_kill_msg(object victim, object killer)
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, format_message(_kill_msg, this_object(), victim));
}

public nomask void
set_create_msg(string val)
{
    if (is_create_done()) {
        error("set_create_msg() must be called in create()");
    }
    _create_msg = val;
}

public nomask string
query_create_msg()
{
    return _create_msg;
}

public nomask void
set_destroy_msg(string val)
{
    if (is_create_done()) {
        error("set_destroy_msg() must be called in create()");
    }
    _destroy_msg = val;
}

public nomask string
query_destroy_msg()
{
    return _destroy_msg;
}

public nomask void
set_die_msg(string val)
{
    if (is_create_done()) {
        error("set_die_msg() must be called in create()");
    }
    _die_msg = val;
}

public nomask string
query_die_msg()
{
    return _die_msg;
}

public nomask void
set_kill_msg(string val)
{
    if (is_create_done()) {
        error("set_kill_msg() must be called in create()");
    }
    _kill_msg = val;
}

public nomask string
query_kill_msg()
{
    return _kill_msg;
}
