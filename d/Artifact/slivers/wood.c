#include "/d/Artifact/artifact.h"

#define P_WOOD ("art_wood")

inherit ART_I_QUIRK;

private string _wood;

static void
create() 
{
    ::create();
    _wood = EMP_D_WOOD->random_wood();
    set_slot("quirk", -1);
}

public int
can_use(object ply, object wpn) 
{
    string str;
    if (!::can_use(ply, wpn)) {
        return 0;
    }
    if (!objectp(wpn)) {
        return 1;
    }
    if (!wpn->query_property("wood")) {
        return notify_fail(capitalize(add_article(wpn->query_shape())) + 
                           " can not be made of wood.");
    }
     if (stringp(str = wpn->query_property(P_WOOD))) {
        return notify_fail("You can not be made of both " + str + 
                           " and " + _wood + ".");
    }
    return 1;
}

static void
setup_weapon(object obj) 
{
    ::setup_weapon(obj);
    if (obj->id("spear") || obj->id("staff")) {
        obj->set_pre_title(_wood + " ");
    }
    obj->add_property(P_WOOD, _wood);
}

static void
unset_weapon(object obj) 
{
    ::unset_weapon(obj);
    if (obj->id("spear") || obj->id("staff")) {
        obj->remove_pre_title(_wood + " ");
    }
    obj->remove_property(P_WOOD);
}

public string
extra_look() 
{
    object obj;
    if (!objectp(obj = query_weapon())) {
        return 0;
    }
    if (obj->id("axe") || obj->id("mace")) { 
        return "#P handle is made of " + _wood;
    }
    if (obj->id("spear") || obj->id("staff")) {
        return "#O is made of " + _wood;
    }
    return 0;
}

