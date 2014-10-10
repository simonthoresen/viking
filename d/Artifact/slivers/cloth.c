#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private string _cloth;

static void
create()
{
    ::create();
    _cloth = EMP_D_COLOR->random_color() + " " + EMP_D_CLOTH->random_cloth();
    set_slot("quirk", -1);
    add_hook("__Artifact_set_weapon", store_fp("on_set_weapon"));
}

static void
on_set_weapon(object prev, object next)
{
    if (objectp(prev)) {
        prev->add_property("cloth", prev->query_property("cloth") - 1);
    }
    if (objectp(next)) {
        next->add_property("cloth", next->query_property("cloth") + 1);
    }
}

public string
extra_look()
{
    object obj;
    if (!objectp(obj = query_weapon())) {
        return 0;
    }
    if (obj->id("axe") || obj->id("spear")) {
        return "Strips of " + _cloth + " are tied just underneath #p head";
    }
    if (obj->id("mace") || obj->id("staff")) {
        return "Strips of " + _cloth + " are tied around #p handle";
    }
    if (obj->id("sword")) {
        return "Strips of " + _cloth + " are tied to #p pommel";
    }
    return 0;
}
