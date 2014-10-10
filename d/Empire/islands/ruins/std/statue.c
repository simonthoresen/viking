#include "/d/Empire/islands/ruins.h"

inherit EMP_I_ITEM;

private string *_kill_reqs;
private string  _npc_file;
private string  _player_msg;
private string  _room_msg;

static void
create()
{
    ::create();
    _kill_reqs  = ({ });
    _npc_file   = 0;
    _player_msg = 0;
    _room_msg   = 0;

    set_name("statue");
    set_get(NO_GET);
    add_hook("__long", store_fp("on_long"));
    add_hook("__reset", store_fp("on_reset"));
    add_trigger("touch", store_fp("do_touch"));
}

private int
can_spawn()
{
    int i, len;
    for (i = 0, len = sizeof(_kill_reqs); i < len; ++i) {
        if (RUN_D_RUINS->can_spawn(_kill_reqs[i])) {
            return 0;
        }
    }
    return RUN_D_RUINS->can_spawn(_npc_file);
}

static string
on_long()
{
    return can_spawn() ? "Its eyes are glowing brightly." : 0;
}

static int
on_reset(int not_first)
{
    if (can_spawn()) {
        remove_property("cold");
        add_property("warm");
        add_property("dangerlevel", 100);
    } else {
        remove_property("dangerlevel");
        remove_property("warm");
        add_property("cold");
    }
}

static int
do_touch(string arg)
{
    object npc;
    if (!stringp(arg) || !id(arg)) {
        return notify_fail("Touch what?");
    }
    if (!can_spawn() || !objectp(npc = RUN_D_RUINS->try_spawn(_npc_file))) {
        say(this_player()->query_name() + " touches the statue.\n");
        write("The statue is cold.\n");
        return 1;
    }
    hook("__open", ({ this_player(), this_object(), npc }));
    write(format_message(_player_msg, npc));
    say(format_message(_room_msg, npc));
    npc->move_player("", this_object());
    return 1;
}

public nomask void
add_kill_req(string val)
{
    _kill_reqs += ({ val });
}

public nomask void
set_kill_reqs(string *val)
{
    _kill_reqs = val;
}

public nomask string *
query_kill_reqs()
{
    return _kill_reqs;
}

public nomask void
set_npc_file(string val)
{
    _npc_file = val;
}

public nomask string
query_npc_file()
{
    return _npc_file;
}

public nomask void
set_player_msg(string val)
{
    _player_msg = val;
}

public nomask string
query_player_msg()
{
    return _player_msg;
}

public nomask void
set_room_msg(string val)
{
    _room_msg = val;
}

public nomask string
query_room_msg()
{
    return _room_msg;
}
