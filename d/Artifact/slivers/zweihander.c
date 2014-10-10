#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(24);
    set_slot("glyph", 1);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R is a large two-handed sword with a double-edged, " +
            "straight blade. #R has plain guards, while #p hilt ends " +
            "with a pear-shaped heavy pommel. #R is almost two meters " +
            "long.");
    add_weapon_id("sword");
    add_weapon_prop("metal");
    set_weapon_class(20);
    set_weapon_weight(4);
    set_weapon_dtype("slash");
    set_weapon_type("twohanded");
}
