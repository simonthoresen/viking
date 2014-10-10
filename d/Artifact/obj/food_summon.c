#include "/d/Artifact/artifact.h"

inherit I_FOOD;

static void
create()
{
    ::create();
    set_name("bread");
    set_short("a loaf of bread");
    set_long("A large loaf of freshly baked bread.");
    add_id(({ "loaf", "loaf of bread" }));
    set_strength(30);
    set_value(0);
    set_weight(1);
}
