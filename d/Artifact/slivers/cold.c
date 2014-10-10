#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

static void
create()
{
    ::create();
    set_slot("quirk", -1);
}

public int
can_use(object ply, object wpn)
{
    if (!::can_use(ply, wpn)) {
        return 0;
    }
    if (objectp(wpn) && wpn->query_property("warm")) {
        return notify_fail("You can not be both cold and warm.");
    }
    return 1;
}

static void
setup_weapon(object obj)
{
    ::setup_weapon(obj);
    obj->add_property("cold", obj->query_property("cold") + 1);
}

static void
unset_weapon(object obj)
{
    ::unset_weapon(obj);
    obj->add_property("cold", obj->query_property("cold") - 1);
}

public string
extra_look()
{
    object obj;
    if (!objectp(obj = query_weapon())) {
        return 0;
    }
    return "#R feels cold";
}
