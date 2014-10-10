#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private string _fur;

static void 
create() 
{
    ::create();
    _fur = EMP_D_FUR->random_fur();
    set_slot("quirk", -1);
}

static void
setup_weapon(object obj) 
{
    ::setup_weapon(obj);
    obj->add_property("fur", obj->query_property("fur") + 1);
}

static void
unset_weapon(object obj) 
{
    ::unset_weapon(obj);
    obj->add_property("fur", obj->query_property("fur") - 1);
}

public string
extra_look() 
{
    object obj;
    if (!objectp(obj = query_weapon())) {
        return 0;
    }
    return "#P grip is wrapped in " + _fur;
}

