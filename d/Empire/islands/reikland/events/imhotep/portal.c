#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ITEM;

private object *_army;

static void
create()
{
    ::create();
    _army = ({ });

    set_name("shard");
    set_short(0);
    set_get(NO_GET);
    set_heart_beat(1);
    add_hook("__destroy", store_fp("on_destroy"));
}

static void
on_destroy()
{
    _army = _army - ({ 0 });
    _army->command("explode");
    _army->destroy();
}

public void
heart_beat()
{
    object env, dst, obj;
    string island, entry;
    if (!objectp(env = bottom_room())) {
        destroy();
        return;
    }
    if (!stringp(island = env->query_island()) ||
        !stringp(entry = island->query_random_entry()) ||
        !objectp(dst = entry->__bootstrap()))
    {
	return;
    }
    if (sizeof(filter_array(all_inventory(dst), "isliving", FILTER_OB)) >= 5 ||
        sizeof(_army = _army - ({ 0 })) >= 100)
    {
	return;
    }
    obj = new(parse_path("demon"));
    obj->add_hook("__bkill", store_fp("consume_loot"));
    obj->add_hook("__bdie", store_fp("prevent_loot"));

    _army += ({ obj });
    obj->move_player("X", dst);
}

public void
consume_loot(object victim, object killer)
{
    if (!objectp(victim) || interactive(victim)) {
        return;
    }
    all_inventory(victim)->destroy();
    victim->add_money(-victim->query_money());
}

public void
prevent_loot(object killer)
{
    consume_loot(this_object(), killer);
}

public object *
query_army()
{
    return _army;
}
