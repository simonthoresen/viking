#include "/d/Empire/islands/fort.h"

inherit FOR_I_WING;

private object _guard;
private int    _tick;

static void
create()
{
    ::create();
    _guard = 0;
    _tick  = 0;

    add_hook("__enter_inv", store_fp("on_enter_inv"));
    add_hook("__reset", store_fp("on_reset"));
}

private void
clone_guard()
{
    _guard = FOR_D_GUARD->new_instance(query_wing());
    _guard->move_player("", this_object());
}

static nomask void
on_enter_inv(object obj, object from)
{
    if (!objectp(_guard)) {
        clone_guard();
    }
}

public void
living_heart_beat(object ply)
{
    if (objectp(_guard)) {
        _tick = 0;
        return;
    }
    if (_tick == 0) {
        _tick = 1;
        return;
    }
    clone_guard();
}

static void
on_reset(int not_first)
{
    int i, len;
    string *arr;
    if (not_first) {
        return;
    }
    for (i = 0, len = sizeof(arr = query_commands()); i < len; ++i) {
        change_exit(arr[i], EX_FUNC, store_fp("guard_exit"));
    }
}

static int
guard_exit(string dst)
{
    if (!objectp(_guard)) {
        return 0;
    }
    write(_guard->query_name() + " blocks your way.\n");
    say(_guard->query_name() + " blocks " +
        this_player()->query_name() + "'s way.\n");
    return 1;
}
