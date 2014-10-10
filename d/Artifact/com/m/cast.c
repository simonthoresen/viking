#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    object ply, env, wpn, obj;
    if (!objectp(ply = this_player()) ||
        !objectp(wpn = ART_C_WEAPON->get_instance(ply)) ||
        wpn->is_suspended())
    {
        write("You have no physical form.\n");
        return 1;
    }
    if (!objectp(env = wpn->query_room())) {
        return notify_fail("You are not anywhere.");
    }
    if (!stringp(arg)) {
        return notify_fail("Cast what spell?");
    }
    if (!objectp(obj = ART_D_SLIVER->query_spell(arg))) {
        return notify_fail("There is no such spell.");
    }
    if (ply->query_busy_next_round()) {
        return notify_fail("You are too busy to do that right now.");
    }
    if (!wpn->can_add(obj)) {
        return notify_fail(wpn->query_failure_msg());
    }
    if (env->query_property("no_magic")) {
        return notify_fail("The area prevents it.");
    }
    ply->set_busy_next_round();
    write("You cast " + obj->query_name() + "!\n");
    clone_object(obj)->move(wpn);
    return 1;
}

public string
short_help()
{
    return "Cast a spell.";
}
