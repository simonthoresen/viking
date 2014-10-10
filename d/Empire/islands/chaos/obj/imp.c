#include "/d/Empire/islands/chaos.h"

inherit CAS_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("Chaos imp");
    set_short("a flaming chaos imp");
    set_long("This is a small red imp that is struggling to contain its " +
	     "powerful fire magic.");
    add_id(({ "imp", "flaming imp" }));
    set_race("demon");
    set_level(20 + random(9));
    set_hp(750);
    set_sp(1500);
    add_skill("prot_fire", 100);
    add_hook("__choose_target", store_fp("on_choose_target"));
    load_a_chat(75, ({ store_fp(resolve_path("cast_fireball"), "main") }));
}

static object
on_choose_target(object *arr) 
{
    int len;
    if (!arrayp(arr) || (len = sizeof(arr)) == 0) {
	return 0;
    }
    return arr[random(len)];
}
