#include "/d/Artifact/artifact.h"

inherit ART_I_SLIVER_DESC;

public varargs nomask int
command(string cmd)
{
    return call_weapon("command", cmd);
}

public int
is_idle() 
{
    return call_weapon("is_idle");
}

public int
is_suspended() 
{
    return call_weapon("is_suspended");
}

public varargs nomask void
silence_echo(int cnt)
{
    call_weapon("silence_echo", cnt);
}

public nomask object
query_attack()
{
    return call_weapon("query_attack");
}

public nomask object *
query_attackers()
{
    return call_weapon("query_attackers");
}

public varargs nomask int
hit_player(int dmg, string type, object foe, string loc, object wpn)
{
    return call_weapon("hit_player", dmg, type, foe, loc, wpn);
}

public nomask int
attack()
{
    return call_weapon("attack");
}

public varargs nomask void
message_player(string class, string str)
{
    call_weapon("message_player", class, str);
}

public varargs nomask void
message_owner(string class, string str)
{
    call_weapon("message_owner", class, str);
}

public varargs nomask void
message_room(string class, mixed str, mixed exclude)
{
    call_weapon("message_room", class, str, exclude);
}

public nomask int
query_avg_skill()
{
    mapping dat;
    string *arr;
    object ply;
    int i, len, val;
    if (!objectp(ply = query_player()) || !mapp(dat = query_skill_reqs())) {
        return 0;
    }
    val = 0;
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        val += ply->query_skill(arr[i]);
    }
    val /= len;
    if (val < 0) {
        val = 0;
    }
    if (val > 100) {
        val = 100;
    }
    return val;
}

public nomask void
setup_modifier(object ply, string mod, int val)
{
    ply->set_modifier(object_name(this_object()) + "#" + mod,
                      mod, "magic", val);
}

public nomask void
unset_modifier(object ply, string mod)
{
    ply->remove_modifier(object_name(this_object()) + "#" + mod);
}
