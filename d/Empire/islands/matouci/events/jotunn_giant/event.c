#include "/d/Empire/empire.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("You hear a pig squeal nearby.\n");
    add_hook("__open", store_fp("create_shard"));
}

static void
create_shard(object ply, object env) 
{
    object obj;
    obj = new(resolve_path("shard"));
    obj->set_player(ply);
    obj->move(env);
}
