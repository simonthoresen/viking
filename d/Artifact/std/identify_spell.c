#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

static void 
create() 
{
    ::create();
    if (query_rank() > 3) {
        error("Expected rank 1-3, got " + query_rank() + ".");
    }
}

public nomask string
query_info() 
{
    string str;
    str = query_name() + " identifies the magical properties of items ";
    switch (query_rank()) {
    case 1:
        str += "carried by the artifact";
        break;
    case 2:
        str += "carried by the artifact's owner";
        break;
    case 3:
        str += "in the environment of the artifact";
        break;
    }
    str += ".";
    return str;
}

public void
identify_item(object obj)
{
    if (!objectp(obj) || !stringp(obj->short())) {
        return;
    }
    tell_object(query_player(), obj->query_name() + ": " + obj->query_info());
}

static void 
setup_weapon(object ply)
{
    object obj;
    ::setup_weapon(ply);
    switch (query_rank()) {
    case 1:
        obj = query_player();
        break;
    case 2:
        obj = query_owner();
        break;
    case 3:
        obj = query_room();
        break;
    }
    map_array(all_inventory(obj), "identify_item");
}
