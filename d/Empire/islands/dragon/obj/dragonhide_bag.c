#include "/d/Empire/islands/dragon.h"

inherit I_CONTAINER;

static void
create()
{
    ::create();
    set_name("bag");
    set_short("a bag of dragonhide");
    set_long("It is a crimson red bag made out of dragonhide. It weighs " +
             "close to nothing, but is still capable of holding an enormous " +
             "amount of stuff.");
    add_id("dragonhide bag");
    add_property(({ "artifact", "leather", "tagged" }));
    set_weight(1);
    set_max_weight(66);
    set_value(6666);
    add_hook("__bwear_out", store_fp("prevent_wear"));
}

static int
prevent_wear(int val, string type)
{
    return 1;
}
