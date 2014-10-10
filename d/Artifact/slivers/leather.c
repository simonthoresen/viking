#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private string _leather;

static void 
create() 
{
    ::create();
    _leather = EMP_D_LEATHER->random_leather();
    set_slot("quirk", -1);
}

static void
setup_weapon(object obj) 
{
    ::setup_weapon(obj);
    obj->add_property("leather", obj->query_property("leather") + 1);
}

static void
unset_weapon(object obj) 
{
    ::unset_weapon(obj);
    obj->add_property("leather", obj->query_property("leather") - 1);
}

public string
extra_look() 
{
    return "#P grip is covered by " + _leather;
}

