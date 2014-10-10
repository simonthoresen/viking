#include "/d/Artifact/artifact.h"

inherit I_DRINK;

static void
create()
{
    ::create();
    set_name("water");
    set_short("a bottle of water");
    set_long("A bottle of crystal clear water.");
    add_id(({ "bottle", "bottle of water" }));
    set_soft_strength(33);
    set_heal(32);
    set_value(0);
    set_weight(1);
    set_empty_container("bottle");
}
