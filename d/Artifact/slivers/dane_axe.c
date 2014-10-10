#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(13);
    set_slot("quirk", 5);

    set_weapon_long(
            "#R has a wide, thin blade, with pronounced horns at both " +
            "the toe and heel of the bit. #P blade is light and forged " +
            "very thin, making #o superb for cutting. #R is about a " +
            "meter long.");
    add_weapon_id("axe");
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtype("chop");
}
