#include "/d/Empire/islands/chaos.h"

inherit EMP_I_ITEM;

private string *_critters;
private object *_army;
private int    *_road;
private int     _num_summoned;

static void
create() 
{
    ::create();
    _critters     = CAS_ISLAND->query_critters();
    _army         = ({ });
    _road         = ({ });
    _num_summoned = 0;
    set_name("chaos portal");
    set_short("a portal to the realm of CHAOS");
    set_long("It it an enormously large stone frame floating mid-air, " +
	     "holding a swirling pink vortex in place.");
    add_id("portal");
    set_get(NO_GET);
    set_heart_beat(1);
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
    destroy(60 * 60);
}

static void
on_move(object from, object to) 
{
    string prev, next;
    if (objectp(from)) {
        EMP_LOG("chaos", "portal closed in " + file_name(from));
	CAS_R_PORTAL->set_portal_exit(0);
	from->remove_exit("portal");
	prev = from->query_island();
    } else {
	prev = 0;
    }
    if (objectp(to)) {
        EMP_LOG("chaos", "portal opened in " + file_name(to));
	CAS_R_PORTAL->set_portal_exit(to);
	to->add_exit(CAS_R_PORTAL, "portal");
	next = to->query_island();
    } else {
	next = 0;
    }
    if (prev == next) {
	return;
    }
    if (stringp(prev)) {
	_army = _army - ({ 0 });
	_army->command("explode");
	_army->destroy();
	_army = ({ });
	_road = ({ });
    }
    if (stringp(next)) {
	_army = filter_array(next->query_livings(), "is_army");
	_road = keys(next->create_road_map());
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public void
heart_beat() 
{
    object obj, env;
    string island;
    if (!objectp(env = environment())) {
	destroy();
	return;
    }
    if (sizeof(filter_array(all_inventory(env), "isliving", FILTER_OB)) >= 5 ||
        sizeof(_army = _army - ({ 0 })) >= 20 ||
        ++_num_summoned > 50) 
    {
	return;
    }
    obj = new(_critters[random(sizeof(_critters))]);
    obj->add_hook("__bkill", store_fp("consume_loot"));
    obj->add_hook("__bdie", store_fp("prevent_loot"));
    _army += ({ obj });

    obj->move_player("", env);
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
