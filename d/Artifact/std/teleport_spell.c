#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private string _location_id;

static void 
create() 
{
    ::create();
    _location_id = 0;
    set_info(query_name() + " teleports the artifact and its wielder " +
             "to a location that was previously remembered.");
}

static void
setup_player(object ply)
{
    object env, usr;
    string dst;
    ::setup_player(ply);
    if (query_room()->query_property("no_teleout")) {
        fizzle_spell("The area prevents it.");
        return;
    }
    if (!stringp(dst = ply->query_property(_location_id))) {
        fizzle_spell("You have not remembered an area for this spell.");
        return;
    }
    if (file_size(dst + ".c") < 0) {
        fizzle_spell("The area you have remembered no longer exists.");
        return;
    }
    if (objectp(usr = query_owner())) {
        if (objectp(usr->query_attack())) {
            fizzle_spell(usr->query_name() + " is too busy right now.");
            return;
        }
        usr->move_player("X", dst);
    } else {
        tell_room(env, ply->query_name() + " leaves in a puff of smoke.\n");
        tell_room(dst->__bootstrap(), ply->query_name() + " arrives in " +
                  "a puff of smoke.\n");
        query_weapon()->move(dst);
    }
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
