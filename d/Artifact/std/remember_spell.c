#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private string _location_id;

static void 
create() 
{
    ::create();
    _location_id = 0;
    set_info(query_name() + " remembers the current location of the " +
             "artifact, so that it can later be teleported to.");
}

static void
setup_player(object ply)
{
    object env;
    ::setup_player(ply);
    if (clonep(env = query_room()) || 
        env->query_property("no_telein") ||
        !env<-I_ROOM)
    {
        fizzle_spell("The area prevents it.");
        return;
    }
    tell_object(ply, "You remember this location.\n");
    ply->add_property(_location_id, source_file_name(env));
}

public nomask void
set_location_id(string val)
{
    _location_id = val;
}

public nomask string
query_location_id()
{
    return _location_id;
}
