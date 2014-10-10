#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(7);
    set_slot("glyph", 2);

    set_weapon_long(
            "#R is a three meter long wooden stick with a sharpened " +
            "head.");
    add_weapon_id("spear");
    add_weapon_prop("wood");
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtype("pierce");
    set_weapon_type("twohanded");
}
