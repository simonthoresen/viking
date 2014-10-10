#include "/d/Artifact/artifact.h"

inherit base ART_I_SPELL;
inherit util ART_I_DAMAGE_UTIL;

static void 
create() 
{
    base::create();
    util::create();
}

public nomask string
query_info() 
{
    return query_name() + " inflicts " + query_dtype() + " damage on " +
           "whoever the wielder of the artifact is attacking.";
}

static void
setup_user(object usr)
{
    object foe;
    ::setup_user(usr);
    if (query_room()->query_property("no_mattack")) {
        fizzle_spell("The area prevents it.");
        return;
    }
    if (!objectp(foe = usr->query_attack())) {
        fizzle_spell(usr->query_name() + " is not attacking anyone.");
        return;
    }
    apply_damage(query_player(), usr, foe);
}

