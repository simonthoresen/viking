#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(15);
    set_slot("glyph", 1);
    set_slot("spell", 1);

    set_weapon_long(
            "#R is a two meter long hammer with a heavy metal head. " +
            "There is a spike on the back side of #p head.");
    add_weapon_ids(({ "mace", "hammer" }));
    add_weapon_props(({ "metal", "wood" }));
    set_weapon_class(15);
    set_weapon_weight(3);
    set_weapon_dtypes(({ "blunt", "blunt", "blunt", "pierce" }));
    set_weapon_type("twohanded");
}
