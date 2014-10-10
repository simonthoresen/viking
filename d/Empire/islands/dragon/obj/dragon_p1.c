#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_HEAD;

private int _flying;

static void create() {
    ::create();
    _flying = 0;

    set_wc(100);
    add_hook("__damage_done", store_fp("maybe_fly"));
    load_a_chat(50, ({ store_fp(resolve_path("cast_bite"), "main"), 
                       store_fp(resolve_path("cast_elemball"), "main"), 
                       store_fp(resolve_path("cast_slam"), "main") }));
}

static void maybe_fly(int dmg, string type, object foe, string loc) {
    object env;
    string island;
    if (_flying != 0 || (query_hp() * 100) / query_max_hp() > 65) {
        return;
    }
    if (objectp(env = environment()) &&
        stringp(island = env->query_island())) 
    {
        island->tell_island(bold("\n\nONYXIA SPREADS HER WINGS!\n\n\n"));
    }
    _flying = 1;
    call_out("do_fly", 2);
}

public void do_fly() {
    object env;
    string island;
    if (objectp(env = environment()) &&
        stringp(island = env->query_island())) 
    {
        island->tell_island(bold("\n\nONYXIA TAKES TO THE SKY!\n\n\n"));
    }
    init_phase(2);
}
