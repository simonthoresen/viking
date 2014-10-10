#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(23);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R is a long-bearded axe. #P cutting edge extends below " +
            "the width of the butt to provide a wide cutting surface " +
            "while keeping the overall weight of the axe low. #R is " +
            "about a meter long.");
    add_weapon_id("axe");
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(15);
    set_weapon_weight(3);
    set_weapon_dtype("chop");
}
