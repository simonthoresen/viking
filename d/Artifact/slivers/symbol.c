#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private string _symbol;

static void 
create() 
{
    ::create();
    _symbol = EMP_D_SYMBOL->random_symbol();
    set_slot("quirk", -1);
}

public string
extra_look() 
{
    object obj;
    if (!objectp(obj = query_weapon())) {
        return 0;
    }
    if (obj->id("axe") || obj->id("sword")) { 
        return capitalize(add_article(_symbol)) + " is etched into the metal";
    }
    if (obj->id("mace") || obj->id("spear") || obj->id("staff")) {
        return capitalize(add_article(_symbol)) + " is burned into the wood";
    }
    return 0;
}

