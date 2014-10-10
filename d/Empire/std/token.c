/**
 * I am aware that this token object has some weird semantics with its implicit
 * 1 count and no set_amount() function. However, this is very much intentional
 * to prevent someone from doing stupid things like:
 *
 * make(MY_TOKEN, this_player())->set_amount(10)
 *
 * Although it looks harmless, the make() call implies a move() to the player,
 * which in turn consumes all other token objects on him. If you follow that
 * with a set_amount() call you will rob the player of all his tokens.
 */
#include "/d/Empire/empire.h"

inherit EMP_I_ITEM;

private int _amount;

static void
create()
{
    ::create();
    _amount = 1;

    set_value(0);
    set_weight(0);
    add_property(({ "tagged", "protected" }));
    add_hook("__bdrop", store_fp("prevent_drop"));
    add_hook("__bwear_out", store_fp("prevent_wear"));
    add_hook("__move", store_fp("on_move"));
}

public void
add_amount(int val)
{
    _amount += val;
    if (_amount <= 0) {
        /* use call_out() here to avoid breaking other code that expects the
           object to be around after calling add_amount() */
        destroy_later();
    }
}

public int
query_amount()
{
    return _amount;
}

public string
query_auto_load()
{
    return source_file_name() + ":" + _amount;
}

public void
init_arg(string arg)
{
    int val;
    if (!sscanf(arg, "%d", val)) {
	val = 1;
    }
    add_amount(val - 1);
}

static int
prevent_drop(int silent)
{
    object ply;
    if (objectp(ply = environment()) && ply->is_pc()) {
        return NO_DROP;
    }
    return CAN_DROP;
}

static int
prevent_wear(int val, string type)
{
    return 1;
}

static void
on_move(object from, object to)
{
    if (!objectp(to)) {
	return;
    }
    map_array(all_inventory(to), "consume_token");
}

static void
consume_token(object obj)
{
    if (!objectp(obj) ||
	obj == this_object() ||
        source_file_name(obj) != source_file_name())
    {
        return;
    }
    add_amount(obj->query_amount());
    obj->destroy();
}
