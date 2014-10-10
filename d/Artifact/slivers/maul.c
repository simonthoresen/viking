#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(5);
    set_slot("glyph", 1);
    set_slot("spell", 1);

    set_weapon_long("#R is a long-handled hammer with a heavy metal head.");
    add_weapon_id("mace");
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtype("blunt");
    set_weapon_type("twohanded");
}
