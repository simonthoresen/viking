#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_HEAD;

static void create() {
    ::create();
    set_wc(125);
    load_a_chat(50, ({ store_fp(resolve_path("cast_bite"), "main"), 
                       store_fp(resolve_path("cast_elemball"), "main"), 
                       store_fp(resolve_path("cast_fear"), "main"), 
                       store_fp(resolve_path("cast_frenzy"), "main"), 
                       store_fp(resolve_path("cast_slam"), "main"), 
                       store_fp(resolve_path("summon_eruption"), "main") }));
}
