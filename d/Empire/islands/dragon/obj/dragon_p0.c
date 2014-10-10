#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_MAIN;

static void create() {
    ::create();
    set_short("an ENORMOUS sleeping dragon");
    set_bored_secs(0);
    set_aggressive(0);
    set_wandering_chance(0);
    add_hook("__bdie", store_fp("prevent_death"));
    add_hook("__battack", store_fp("awaken_beauty"));
}

static int prevent_death(object foe) {
    return 1;
}

static int awaken_beauty(object foe) {
    object env;
    string island;
    if (!objectp(env = environment())) {
        return 1; /* ehrm */
    }
    if (DON_D_DRAGON->query_next_time() > time()) {
        tell_room(env, "Onyxia vanishes in a puff of smoke.\n");
        call_out("destroy", 0);
        return 1;
    }
    if (stringp(island = env->query_island())) {
        island->tell_island(bold("\n\nONYXIA HAS AWAKENED\n\n\n"));
    }
    init_phase(1);
    return 1;
}

