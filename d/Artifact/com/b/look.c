#include "/d/Artifact/artifact.h"

inherit "/com/g/look";

static object
locate(string str, object ply, object env) 
{
    object obj;
    if (objectp(obj = ::locate(str, ply, env))) {
        return obj;
    }
    return present(str, ply->query_owner());
}

public void 
show_items(object *arr, object ply) 
{
    ::show_items(arr - ({ ply->query_weapon(), ply->query_owner() }), ply);
}
