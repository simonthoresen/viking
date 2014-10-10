#include "/d/Artifact/artifact.h"

inherit base CMD_MODULE;
inherit util EMP_I_FEELINGS;

static void 
create() 
{
    base::create();
    util::create();
}

static object
find_target(object actor, string arg)
{
    object ply;
    if (!objectp(ply = find_player(arg)) ||
        !ART_MASTER->is_member(ply))
    {
        return 0;
    } 
    return ply;
}

static void
notify_actor(object actor, string msg)
{
    message("channels", "[Artifact]: " + msg, actor);
}

static void
notify_target(object target, string msg)
{
    message("channels", "[Artifact]: " + msg, target);
}

static void
notify_audience(object actor, object target, string msg)
{
    message("channels", "[Artifact]: " + msg, ART_MASTER->query_members(),
            ({ actor, target }));
}

static int
main(string arg) 
{
    if (!stringp(arg)) {
        return notify_fail("Say what?");
    }
    if (sscanf(arg, "emote: %s", arg)) {
        ART_MASTER->broadcast(this_player()->query_name() + " " + arg);
        return 1;
    } 
    if (sscanf(arg, "feeling: %s", arg)) {
        return perform_feeling(this_player(), arg);
    }
    ART_MASTER->broadcast(arg, this_player());
    return 1;
}

public string
short_help() 
{
    return "Chat with the other online Artifacts.";
}
