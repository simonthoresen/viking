#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(12);
    set_slot("spell", 1);

    set_weapon_long(
            "#R is a one-handed mace with metal flanges protruding from " +
            "#p head. It is just short of a meter long.");
    add_weapon_id("mace");
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtype("blunt");
}
