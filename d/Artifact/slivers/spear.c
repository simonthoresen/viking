#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(17);
    set_slot("glyph", 2);

    set_weapon_long(
            "#R is a long wooden stick with a metal spearhead shaped " +
            "like a barbed triangle. Near #p head the shaft has been " +
            "reinfored with metal strips.");
    add_weapon_id("spear");
    add_weapon_props(({ "metal", "wood" })); 
    set_weapon_class(15);
    set_weapon_weight(3);
    set_weapon_dtype("pierce");
    set_weapon_type("twohanded");
}
