#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_EVENT;

static void
create()
{
    ::create();
    set_player_msg("A raggedy looking man bumps into you.\n");
    set_room_msg("A raggedy looking man bumps into #N.\n");
    add_hook("__open", store_fp("pick_pocket"));
}

static void
pick_pocket(object ply, object env)
{
    object obj;
    if (!objectp(ply) || !objectp(env)) {
	return;
    }
    obj = make(resolve_path("thief"), env);
    obj->try_pick_pocket(ply);
}

public void
notify_pit(object ply, string name, int idx)
{
    string str;
    if (!objectp(ply) || !stringp(name) || idx > 5) {
        return;
    }
    switch (idx) {
    case 0:
        str = "[INFO]: " + name + " leaves the game.\n";
        break;
    case 1:
        str = "[INFO]: " + name + " enters the game.\n";
        break;
    case 2:
        str = name + " [Chat]: Damn, " + ply->query_name() + " killed me " +
              "because I lagged too much!\n";
        break;
    case 3:
        str = name + " [Chat]: I guess you're pretty proud of yourself " +
              "now, " + ply->query_name() + "?!\n";
        break;
    case 4:
        str = name + " [Chat]: You can't imagine how much exp I lost :(\n";
        break;
    case 5:
        str = "[INFO]: " + name + " screams as he is torn apart in the " +
              "pit.\n";
        break;
    }
    message("channels", str, ply);
    call_out("notify_pit", 5 + random(5), ply, name, idx + 1);
}
