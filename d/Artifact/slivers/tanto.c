#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(9);
    set_slot("glyph", -1);
    set_slot("quirk", 10);

    set_weapon_long(
            "#R is a double edged oriental dagger with a thick cross-" +
            "section and a wooden handle. #R is about a quarter of a " +
            "meter long.");
    add_weapon_ids(({ "katana", "sword" }));
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(5);
    set_weapon_weight(1);
    set_weapon_dtype("pierce");
}
