#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ITEM;

static void
create() 
{
    ::create();
    set_name("stone");
    set_short(({
        "a burning shard of a meteor",
        "a shard of a meteor",
        "a fuming piece of stone",
        "a piece of stone",
        "a glowing meteor-shard" 
    })[random(5)]);
    set_long(capitalize(query_short())+".");
    set_weight(10 + random(20));
    add_property("warm");
    add_hook("__destroy", store_fp("on_destroy"));
    destroy(20 + random(20));
}

static void
on_destroy() 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    message("", capitalize(short()) + " burns to ashes.\n", env);
}
