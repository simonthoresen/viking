#include "/d/Artifact/artifact.h"

inherit I_MONSTER;

static void
create()
{
    ::create();
    add_property("no_nothing");
    add_hook("__bnotify_attack", store_fp("on_bnotify_attack"));
    add_hook("__bdie", store_fp("on_bdie"));
    add_hook("__catch_tell", store_fp("on_catch_tell"));
}

static int
on_bnotify_attack(object foe)
{
    return 1;
}

static int
on_bdie(object foe)
{
    return 1;
}

static void
on_catch_tell(string msg)
{
    receive_message("", msg);
}

static void
receive_message(mixed class, string msg)
{
    object env, wpn;
    if (!objectp(env = environment()) ||
        !objectp(wpn = env->query_weapon()) ||
        !objectp(env = wpn->query_room()))
    {
        return;
    }
    message(class, msg, env, wpn->query_echo());
}
