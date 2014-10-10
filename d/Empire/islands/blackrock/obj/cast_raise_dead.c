#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

static int
do_cast(object ply, object foe)
{
    object obj;
    ply->command("emote raises the undead!");
    obj = new(resolve_path("skeleton"));
    obj->set_dangerlevel((ply->query_dangerlevel() * 2) / 3);
    obj->move_player("x", environment(ply));
    obj->do_attack(foe);
    obj->destroy(60, store_fp("on_destroy"));
    return 1;
}

public int
on_destroy()
{
    object obj, env;
    if (!objectp(obj = previous_object()) ||
        !objectp(env = environment(obj)))
    {
        return 0;
    }
    tell_room(env, obj->query_name() + " vanishes in a puff of smoke.\n");
    return 0;
}
