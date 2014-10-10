#include "/d/Artifact/artifact.h"
#define P_METAL ("art_metal")

inherit ART_I_QUIRK;

private string _metal;

static void
create()
{
    ::create();
    _metal = lower_case(query_name());
    set_info(query_name() + " turns the artifact into " + _metal + ".");
}

public int
can_use(object ply, object wpn)
{
    string str;
    if (!::can_use(ply)) {
        return 0;
    }
    if (!objectp(wpn)) {
        return 1;
    }
    if (!wpn->query_property("metal")) {
        return notify_fail(capitalize(add_article(wpn->query_shape())) +
                           " can not be made of metal.");
    }
    if (stringp(str = wpn->query_property(P_METAL))) {
        return notify_fail("You can not be made of both " + str +
                           " and " + _metal + ".");
    }
    return 1;
}

static void
setup_weapon(object obj)
{
    ::setup_weapon(obj);
    if (obj->id("axe") || obj->id("mace") || obj->id("sword")) {
        obj->add_pre_title(_metal + " ");
    }
    obj->add_property(P_METAL, _metal);
    obj->add_property(_metal);
}

static void
unset_weapon(object obj)
{
    ::unset_weapon(obj);
    if (obj->id("axe") || obj->id("mace") || obj->id("sword")) {
        obj->remove_pre_title(_metal + " ");
    }
    obj->remove_property(P_METAL);
    obj->remove_property(_metal);
}

public string
extra_look()
{
    object obj;
    if (!objectp(obj = query_weapon())) {
        return 0;
    }
    if (obj->id("axe") || obj->id("mace")) {
        return "#P head is made of " + _metal;
    }
    if (obj->id("spear")) {
        return "#P tip is made of " + _metal;
    }
    if (obj->id("sword")) {
        return "#P blade is made of " + _metal;
    }
    return 0;
}

public nomask string
query_metal()
{
    return _metal;
}
