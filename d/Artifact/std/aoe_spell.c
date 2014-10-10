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
           "everyone who is attacking the wielder of the artifact.";
}

static void
setup_user(object usr)
{
    int i, len;
    object *arr;
    ::setup_user(usr);
    if (query_room()->query_property("no_mattack")) {
        fizzle_spell("The area prevents it.");
        return;
    }
    arr = usr->query_attackers();
    len = sizeof(arr);
    if (len == 0) {
        fizzle_spell("Noone is attacking " + usr->query_name() + ".");
        return;
    }
    for (i = 0; i < len; ++i) {
        apply_damage(query_player(), usr, arr[i]);
    }
}
