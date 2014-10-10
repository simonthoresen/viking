#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(27);
    set_slot("glyph", 2);

    set_weapon_long(
            "#R is a thrusting spear. #R consists of a lozenge shaped " +
            "head, beneath which on the socket there are prominent " +
            "wings.");
    add_weapon_id("spear");
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(20);
    set_weapon_weight(4);
    set_weapon_dtype("pierce");
    set_weapon_type("twohanded");
}
