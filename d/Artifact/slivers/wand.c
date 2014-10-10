#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(8);
    set_slot("glyph", -1);
    set_slot("spell", 2);

    set_weapon_long("#R is a thin, straight, hand-held stick of wood.");
    add_weapon_id("staff");
    add_weapon_prop("wood");
    set_weapon_class(5);
    set_weapon_weight(1);
    set_weapon_dtype("blunt");
}
