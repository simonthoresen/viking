#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(26);
    set_slot("spell", 1);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R is an axe with a heavy crescent-shaped head mounted " +
            "on a long wooden shaft. It is almost one and a half " +
            "meter long.");
    add_weapon_id("axe");
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(20);
    set_weapon_weight(4);
    set_weapon_dtype("chop");
    set_weapon_type("twohanded");
}
