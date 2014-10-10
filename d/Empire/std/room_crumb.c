#include "/d/Empire/empire.h"

inherit EMP_I_ROOM_BASE;

private string _crumb;
private int    _crumb_duration;
private int    _crumb_time;

static void
create()
{
    ::create();
    _crumb          = 0;
    _crumb_duration = -1;
    _crumb_time     = 0;

    add_hook("__perform_move", store_fp("leave_crumb"));
}

static nomask void
leave_crumb(string dir, string dst)
{
    object ply;
    if (!objectp(ply = this_player()) || !ply->is_pc()) {
        return;
    }
    _crumb = dir;
    _crumb_time = time();
}

public nomask void
set_crumb(string val)
{
    _crumb = val;
    _crumb_time = time();
}

public nomask string
query_crumb()
{
    if (_crumb_duration >= 0 &&
        _crumb_duration + _crumb_time < time())
    {
        return 0;
    }
    return _crumb;
}

public nomask void
set_crumb_duration(int val)
{
    _crumb_duration = val;
}

public nomask int
query_crumb_duration()
{
    return _crumb_duration;
}
