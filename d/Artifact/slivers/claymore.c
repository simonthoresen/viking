#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(14);
    set_slot("glyph", 1);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R is a long sword with a broad double edged blade. #R " +
            "has a wheel pommel capped with a crescent-shaped nut, and " +
            "guarded with straight down-sloping arms ending in " +
            "quatrefoils. #R is about one and a half meter long.");
    add_weapon_id("sword");
    set_weapon_class(15);
    set_weapon_weight(3);
    set_weapon_dtype("slash");
    set_weapon_type("twohanded");
}
