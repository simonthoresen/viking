#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(4);
    set_slot("glyph", 1);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R is a sword with a broad double edged blade. #R has a " +
            "basket-shaped guard that protects the hands of #p " +
            "wielder. #R is about a meter long.");
    add_weapon_id("sword");
    add_weapon_prop("metal");
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtype("slash");
    set_weapon_type("twohanded");
}
