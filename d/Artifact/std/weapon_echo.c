#include "/d/Artifact/artifact.h"

inherit ART_I_WEAPON_DESC;

private object _echo;
private int    _silent;

static void
create()
{
    ::create();
    _echo   = 0;
    _silent = 0;

    add_hook("__destroy", store_fp("destroy_echo"));
    add_hook("__move", store_fp("follow_weapon"));
}

private void
ensure_echo()
{
    if (!objectp(_echo)) {
        _echo = new(ART_C_ECHO_WEAPON);
        _echo->set_weapon(this_object());
        _echo->move(query_room());
    }
}

static nomask void
destroy_echo()
{
    if (objectp(_echo)) {
        _echo->destroy();
    }
}

private void
move_echo(object to)
{
    ensure_echo();
    if (!objectp(to) ||
        !objectp(to = query_room(to)) ||
        environment(_echo) == to)
    {
        return;
    }
    _echo->move(to);
    _echo->command("glance");
}

static nomask void
follow_weapon(object from, object to)
{
    if (objectp(from) && living(from)) {
        from->remove_hook("__move");
    }
    if (objectp(to) && living(to)) {
        to->add_hook("__move", store_fp("follow_owner"));
    }
    move_echo(query_room(to));
}

public nomask void
follow_owner(object from, object to)
{
    move_echo(query_room(to));
}

public nomask void
echo_message(string class, string msg)
{
    object ply;
    if (_silent > 0 && --_silent >= 0) {
        return;
    }
    if (!objectp(ply = query_player()) || is_suspended()) {
        return;
    }
    message(class, msg, ply);
}

public varargs nomask void
silence_echo(int cnt)
{
    _silent += max(1, cnt);
}

public object
query_echo()
{
    ensure_echo();
    return _echo;
}

public nomask int
command(string cmd)
{
    EMP_DEBUG(query_player(), "weapon_echo::command('" + cmd + "')");
    ensure_echo();
    return _echo->command(cmd);
}
