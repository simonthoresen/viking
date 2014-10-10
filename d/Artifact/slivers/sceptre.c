#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(18);
    set_slot("glyph", -1);
    set_slot("spell", 2);

    set_weapon_long(
            "#R is a polished wooden staff about a meter long. #R " +
            "is surmounted by a perfectly carved wooden sphere.");
    add_weapon_id("staff");
    add_weapon_prop("wood");
    set_weapon_class(10);
    set_weapon_weight(2);
    set_weapon_dtype("blunt");
}
