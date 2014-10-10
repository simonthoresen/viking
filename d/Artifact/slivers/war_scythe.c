#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(6);
    set_slot("spell", 1);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R is a pole weapon with a short metal blade that extends " +
            "upright from the pole.");
    add_weapon_ids(({ "scythe", "axe" }));
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtype("chop");
    set_weapon_type("twohanded");
}
