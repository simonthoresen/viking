#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(11);
    set_slot("glyph", 1);

    set_weapon_long(
            "#R is a two-edged short-sword with a tapered point. #R " +
            "has a knobbed wooden hilt with ridges for the fingers.");
    add_weapon_id("sword");
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtypes(({ "slash", "slash", "slash", "pierce" }));
}
