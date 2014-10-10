#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private int    _ticks;
private string _boom;

static void
create() 
{
    ::create();
    _ticks = 0;
    _boom  = read_file(resolve_path("boom.art"));

    set_name("Baneling");
    set_short("an EXPLOSIVE baneling");
    set_long("A slimy larva covered in bloated fluid sacks that look " +
             "ready to explode at any time.");
    add_id(({ "creature", "larva", "slimy larva", "explosive baneling" }));  
    set_level(1);
    set_hp(69);
    set_str(1);
    set_dex(1);
    set_wc(0);
    set_ac(0);
    load_a_chat(100, ({ "*say TICK TOCK TICK TOCK TICK TOCK!!" }));
    load_chat(100, ({ "*say TICK TOCK TICK TOCK TICK TOCK!!" }));
    add_hook("__heart_beat", store_fp("on_heart_beat"));
}

static void
on_heart_beat() 
{
    object env;
    if (!objectp(env = environment()) || ++_ticks <= 2) {
        return;
    }
    map_array(all_inventory(env), "throw_player");
    destroy();
}

static void
throw_player(object ply) 
{
    if (!objectp(ply) || !living(ply) || ply->query_invis() ||
        ply->is_crusader()) 
    {
        return;
    }
    if (interactive(ply)) {
	tell_ansi(ply, _boom);
    }
    EMP_D_COMBAT->hit_player(this_object(), ply, 100 + random(100), "fire");
    EMP_D_COMBAT->throw_player(ply, 1);
}

public int 
is_crusader() 
{
    return 1; 
}
