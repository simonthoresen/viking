#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(16);
    set_slot("spell", 1);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R is a two-handed pole axe. The blade is topped with a " +
            "spike, and there is a hook on its back.");
    add_weapon_id("axe");
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(15);
    set_weapon_weight(3);
    set_weapon_dtypes(({ "chop", "chop", "chop", "pierce" }));
    set_weapon_type("twohanded");
}
