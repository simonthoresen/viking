#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(29);
    set_slot("quirk", 10);

    set_weapon_long(
            "#R is a two-handed katana. #R has a curved, slender, " +
            "single edged blade, and a circular guard. #R is one and " +
            "a half meter long.");
    add_weapon_ids(({ "katana", "sword" }));
    add_weapon_prop("metal");
    set_weapon_class(20);
    set_weapon_weight(4);
    set_weapon_dtype("slash");
    set_weapon_type("twohanded");
}
