#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(28);
    set_slot("spell", 2);

    set_weapon_long(
            "#R is a gnarled wooden staff about two meters long. #P " +
            "head is rough and twisted.");
    add_weapon_id("staff");
    add_weapon_prop("wood");
    set_weapon_class(15);
    set_weapon_weight(3);
    set_weapon_dtype("blunt");
    set_weapon_type("twohanded");
}
