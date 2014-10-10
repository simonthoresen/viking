#include "/d/Artifact/artifact.h"

inherit ART_I_WEAPON_ECHO;

private void
do_message(string class, string str, object ply)
{
    if (!objectp(ply)) {
        return;
    }
    if (!stringp(str)) {
        str   = class;
        class = "";
    }
    message(class, str, ply);
}

public varargs nomask void
message_player(string class, string str)
{
    do_message(class, str, query_player());
}

public varargs nomask void
message_owner(string class, string str)
{
    do_message(class, str, query_owner());
}

public varargs nomask void
message_user(string class, string str)
{
    do_message(class, str, query_user());
}

public varargs nomask void
message_room(string class, mixed str, mixed exclude)
{
    object env;
    if (!objectp(env = query_room())) {
        return;
    }
    if (!stringp(str)) {
        exclude = str;
        str     = class;
        class   = "";
    }
    if (!arrayp(exclude)) {
        exclude = ({ exclude });
    }
    if (sizeof(exclude & ({ this_object() })) > 0) {
        exclude += ({ query_echo() });
    }
    message(class, str, env, exclude);
}

public varargs void
force_drop(int silent)
{
    object ply, env;
    if (objectp(ply = query_owner())) {
        ply->drop_one_item(this_object(), silent);
    }
    env = query_room();
    if (environment() != env) {
        move(env);
    }
}
