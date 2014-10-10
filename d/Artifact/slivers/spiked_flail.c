#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void 
create() 
{
    ::create();
    set_level_req(25);
    set_slot("glyph", 1);
    set_slot("spell", 1);

    set_weapon_long(
            "#R is a ball-on-a-chain bludgeon with three spiked metal " +
            "balls attached to a wooden shaft.");
    add_weapon_id("mace");
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(20);
    set_weapon_weight(4);
    set_weapon_dtypes(({ "blunt", "pierce" }));
    set_weapon_type("twohanded");
}
