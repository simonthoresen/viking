#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private string _gemstone;

static void 
create() 
{
    ::create();
    _gemstone = EMP_D_GEMSTONE->random_gemstone();
    set_slot("quirk", -1);
}

public string
extra_look() 
{
    object obj;
    if (!objectp(obj = query_weapon())) {
        return 0;
    }
    if (obj->id("axe") || obj->id("mace") || 
        obj->id("spear") || obj->id("staff")) 
    {
        return capitalize(add_article(_gemstone)) + " is set in #p head";
    }
    if (obj->id("sword")) {
        return capitalize(add_article(_gemstone)) + " is set in #p pommel";
    }
    return 0;
}
