#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    object ply, wpn, usr;
    if (!objectp(ply = this_player()) ||
        !objectp(wpn = ART_C_WEAPON->get_instance(ply)) ||
        wpn->is_suspended())
    {
        write("You have no physical form.\n");
        return 1;
    }
    if (objectp(usr = wpn->query_user()) &&
        objectp(usr->query_attack()))
    {
        return notify_fail("You can not slip while fighting.");
    }
    if (!objectp(usr = wpn->query_owner())) {
        return notify_fail("Noone is carrying you.");
    }
    write("You attempt to slip from " + usr->query_name() + "'s hands.\n");
    if (!usr->drop_one_item(wpn)) {
        return notify_fail("You fail.");
    }
    return 1;
}

public string
short_help()
{
    return "Drop to the ground.";
}
