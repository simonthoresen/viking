#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(19);
    set_slot("glyph", -1);
    set_slot("quirk", 10);

    set_weapon_long(
            "#R is a one-handed katana. #R has a curved, slender, " +
            "single edged blade, and a circular guard. #R is almost " +
            "three-quarters of a meter long.");
    add_weapon_ids(({ "katana", "sword" }));
    add_weapon_prop("metal");
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtype("slash");
}
