#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(22);
    set_slot("spell", 1);

    set_weapon_long(
            "#R is a wooden club with a heavy head made of metal. #R " +
            "has a long spike extending straight from #p head, and " +
            "many smaller spikes around the particle of #p head.");
    add_weapon_ids(({ "star", "mace" }));
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(15);
    set_weapon_weight(3);
    set_weapon_dtypes(({ "blunt", "pierce" }));
}
