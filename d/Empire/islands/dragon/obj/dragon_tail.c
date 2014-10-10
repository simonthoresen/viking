#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_LIMB;

static void create() {
    ::create();
    set_name("Onyxia's tail");
    set_short("the SPIKED tail of Onyxia");
    set_wc(256);
    add_id("tail");
    add_property("unarmed_damage_type", ({ "blunt", "pierce" }));
    add_hook("__attack", store_fp("notify_player"));
    add_hook("__damage_dealt", store_fp("throw_player"));
}

static void notify_player(object foe) {
    object env;
    if (!objectp(foe) || !objectp(env = environment(foe))) {
        return;
    }
    tell_object(foe, "WATCH OUT!! Onyxia swings her tail towards you!!\n");
    tell_room(env, "Onyxia swings her tail towards " + foe->query_name() + 
              ".\n", ({ foe }));
}

static void throw_player(int dmg, string type, object foe, string loc) {
    object env;
    if (!objectp(foe) || 
        !objectp(env = environment(foe)) || 
        dmg < 25) 
    {
        return;
    }
    if (type == "pierce") {
        tell_object(foe, "YOU ARE IMPALED BY ONYXIA'S TAIL!\n");
        tell_room(env, foe->query_name() + " is impaled by Onyxia's tail.\n");
        EMP_D_COMBAT->wound_player(this_object(), foe, dmg * 5);
    } else if (type == "blunt") {
        foe->set_busy_next_round(foe->query_name() + " gets back " +
                                 foe->query_possessive() + " feet.\n");
        EMP_D_COMBAT->throw_player(foe, dmg / 25);
    }
}
