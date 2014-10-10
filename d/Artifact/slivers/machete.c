#include "/d/Artifact/artifact.h"

inherit ART_I_SHAPE;

static void
create() 
{
    ::create();
    set_level_req(1);
    set_slot("glyph", 1);

    set_weapon_long(
            "#R is a large cleaver-like cutting tool. The cutting edge " +
            "of #p blade is curved, widening toward the point, and has " +
            "straight, unsharpened back edge. #P is almost half a meter " +
            "long.");
    add_weapon_ids(({ "dagger", "knife", "sword" }));
    add_weapon_prop("metal");
    set_weapon_class(5);
    set_weapon_weight(1);
    set_weapon_dtype("slash");
}
