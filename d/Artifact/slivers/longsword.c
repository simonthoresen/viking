#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(21);
    set_slot("glyph", 1);

    set_weapon_long(
            "#R is a sword with a cruciform hilt and a grip for one " +
            "handed use. #R has a straight double-edged blade that is " +
            "about meter long.");
    add_weapon_id("sword");
    add_weapon_prop("metal");
    set_weapon_class(15);
    set_weapon_weight(3);
    set_weapon_dtype("slash");
}
