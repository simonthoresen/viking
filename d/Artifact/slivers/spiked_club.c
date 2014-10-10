#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(2);
    set_slot("spell", 1);

    set_weapon_long(
            "#R is a large wooden club with a heavy head on the end. " +
            "There are small studs forged into #p head.");
    add_weapon_id("mace");
    add_weapon_prop("wood");
    set_weapon_class(5);
    set_weapon_weight(1);
    set_weapon_dtypes(({ "blunt", "pierce" }));
}
