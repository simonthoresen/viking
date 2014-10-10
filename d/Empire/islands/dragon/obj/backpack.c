#include "/d/Empire/islands/dragon.h"

inherit I_CONTAINER;

private int _auto_load;

static void
create()
{
    ::create();
    _auto_load = 0;

    set_name("backpack");
    set_short("a backpack of dragon's hide");
    set_long("It is a crimson red backpack made out of dragon hide. It " +
             "weighs close to nothing, but is capable of holding quite " +
             "a lot. You WILL NOT loose this bag!");
    add_id(({ "dragon hide backpack", "dragon backpack",
              "hide backpack", "pack" }));
    add_property(({ "artifact", "leather", "tagged" }));
    set_weight(1);
    set_max_weight(22);
    set_value(6666);
    set_drop(NO_DROP);
    add_hook("__bwear_out", store_fp("prevent_wear"));
    add_hook("__move", store_fp("on_move"));
}

static int
prevent_wear(int val, string type)
{
    return 1;
}

static void
on_move(object from, object to)
{
    if (_auto_load && living(to)) {
	_auto_load = 0;
        tell_object(to, bold("NOTE: To reinstate the Onyxia backpack drop, " +
                             "your bag is being replaced by 3x the new hide " +
                             "reward. Sorry for the inconvenience.\n"));
        call_out("destroy", 0);
        make(DON_DIR_OBJ + "dragonhide", to);
        make(DON_DIR_OBJ + "dragonhide", to);
        make(DON_DIR_OBJ + "dragonhide", to);
    }
}

public string
query_auto_load()
{
    return 0; /*source_file_name() + ":";*/
}

public void
init_arg(string arg)
{
    _auto_load = 1;
}
