#include "/d/Artifact/artifact.h"

inherit I_DRINK;

static void
create()
{
    ::create();
    set_name("liquir");
    set_short("a bottle of liquor");
    set_long("A bottle of crystal clear liquor.");
    add_id(({ "bottle", "bottle of liquor" }));
    set_strength(32);
    set_heal(40);
    set_value(0);
    set_weight(1);
    set_empty_container("bottle");
}
