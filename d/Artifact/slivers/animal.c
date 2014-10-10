#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private string _animal;

static void
create() 
{
    ::create();
    _animal = EMP_D_ANIMAL->random_animal();
    set_slot("quirk", -1);
}

static void
setup_weapon(object wpn)
{
    ::setup_weapon(wpn);
    wpn->add_title(" of the " + _animal);
}

static void
unset_weapon(object wpn)
{
    ::unset_weapon(wpn);
    wpn->remove_title(" of the " + _animal);
}

public string
extra_look() 
{
    object obj;
    if (!objectp(obj = query_weapon())) {
        return 0;
    }
    if (obj->id("axe") || obj->id("sword")) { 
        return "An image of " + add_article(_animal) + 
               " is etched into the metal";
    }
    if (obj->id("mace") || obj->id("spear") || obj->id("staff")) {
        return "An image of " + add_article(_animal) + 
               " is burned into the wood";
    }
    return 0;
}

