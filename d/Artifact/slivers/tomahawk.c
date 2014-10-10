#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(3);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R is a single-handed striking tool with a sharp blade " +
            "and a straight shaft. #R is about half a meter long");
    add_weapon_id("axe");
    add_weapon_prop("wood");
    set_weapon_class(5);
    set_weapon_weight(1);
    set_weapon_dtype("chop");
}
