#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ARMOUR;

private int _auto_load;

static void
create()
{
    ::create();
    _auto_load = 0;

    set_name("shard");
    set_short("a glowing shard");
    set_long("A cone shaped diamond shard that emits a powerfull light.");
    set_info("It may be socketed into a person's head.");
    set_type("brain");

    set_value(1000+random(500));
    set_weight(1);
    set_light(5);
    set_wear_modifier("int", -1, 666);

    add_hook("__move", store_fp("on_move"));
    add_hook("__long", store_fp("on_long"));
    add_hook("__remove", store_fp("on_remove"));
    add_hook("__wear", store_fp("on_wear"));
}

static void
on_move(object from, object to)
{
    if (_auto_load) {
	_auto_load = 0;
	wear(1);
    }
}

static string
on_long()
{
    if (!objectp(query_worn())) {
        return 0;
    }
    return "It has been driven into your forehead. It might be possible, "+
	   "yet dangerous, to remove it.";
}

static void
on_wear(int silent)
{
    object ply;
    if (silent || !objectp(ply = query_worn_by())) {
	return;
    }
    EMP_D_COMBAT->hit_player(ply, ply, 25 + random(25), "pierce",
                             "head", this_object());
}

static void
on_remove(int silent)
{
    object ply;
    if (silent || !objectp(ply = query_worn_by())) {
	return;
    }
    EMP_D_COMBAT->spray_blood(environment(ply), 150);
}

public string
query_auto_load()
{
    if (!objectp(query_worn_by())) {
        return 0;
    }
    return source_file_name() + ":";
}

public void
init_arg(string arg)
{
    _auto_load = 1;
    add_property("tagged");
}

public string
extra_look()
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return 0;
    }
    return format_message("#R has a diamond shard driven into #p forehead", ply);
}
