#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_MAIN;

private int _beat;
private int _landing;

static void create() {
    ::create();
    _beat    = 0;
    _landing = 0;

    setmout("flies");
    add_property("flying");
    set_wc(50);
    set_short("an ENORMOUS dragon flying high above you");
    add_hook("__fight_beat", store_fp("special_attack"));
    add_hook("__hit_player", store_fp("prevent_hityou"));
    add_hook("__damage_done", store_fp("maybe_land"));
    add_hook("__bdie", store_fp("prevent_death"));
    add_property("unarmed_damage_type",
                 ({ "fire", "cold", "electricity", "acid", "magic" }));
}

void special_attack(object foe) {
    if (++_beat >= 40) {
	_beat = 0;
    }
    switch (_beat) {
    case 0:
	resolve_path("cast_elemball")->main(this_object(), foe);
	break;
    case 10:
	resolve_path("summon_whelps")->main(this_object(), foe);
	break;
    case 20:
	resolve_path("cast_deepbreath")->main(this_object(), foe);
	break;
    case 30:
	resolve_path("summon_guard")->main(this_object(), foe);
	break;
    }
}

static int prevent_death(object foe) {
    return 1;
}

static int prevent_hityou(int dmg, string type, object foe, string loc,
                          int prot_mod, int resist_mod, int vuln_mod,
                          int ac_mob, object weapon) 
{
    if ((objectp(weapon) || type == "blunt") && !can_fly(foe)) {
        tell_object(foe, "The dragon is too far away for you to reach.\n");
        return -666999;
    }
    return 0;
}

static void maybe_land(int dmg, string type, object foe, string loc) {
    object env;
    string island;
    if (_landing != 0 || (query_hp() * 100) / query_max_hp() > 40) {
        return;
    }
    if (objectp(env = environment()) &&
        stringp(island = env->query_island())) 
    {
        island->tell_island(bold("\n\nONYXIA IS ABOUT TO LAND!\n\n\n"));
    }
    _landing = 1;
    call_out("do_land", 10);
}

public void do_land() {
    object env;
    string island;
    if (objectp(env = environment()) &&
        stringp(island = env->query_island())) 
    {
        island->tell_island(bold("\n\nONYXIA JUST LANDED!\n\n\n"));
    }
    init_phase(3);
}
