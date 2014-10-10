#include "/d/Empire/islands/dragon.h"

inherit I_ITEM;

static void 
create() 
{
    ::create();
    set_name("dragonhide");
    set_short("a piece of dragonhide");
    set_long("An incredibly light, yet impressively strong piece of " +
             "dragonhide. You can use this to 'craft dragonhide " +
             "bag'. You will not loose this item until you use it.");
    add_id(({ "piece", "hide" }));
    set_value(9999);
    set_weight(0);
    set_drop(NO_DROP);
    add_property(({ "artifact", "leather", "tagged" }));
    add_hook("__bwear_out", store_fp("prevent_wear"));
    add_trigger("craft", store_fp("do_craft"));
}

static int
do_craft(string arg) 
{
    object ply;
    if (arg != "dragonhide bag") {
        return notify_fail("Craft what?");
    }
    write("You craft a bag from your dragonhide.\n");
    say(this_player()->query_name() + " crafts a dragonhide bag.\n");
    make(DON_DIR_OBJ + "dragonhide_bag", this_player());
    destroy();
    return 1;
}

static int
prevent_wear(int val, string type) 
{
    return 1;
}

public string 
query_auto_load() 
{
    return source_file_name() + ":";
}
