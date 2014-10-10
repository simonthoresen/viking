#include <mudlib.h>

inherit I_ARMOUR;

int _next_attack;

void create() {
    ::create();
    _next_attack = 0;

    set_name("Boots of the Minotaur");
    set_short("a pair of dark furred boots");
    set_long("The boots are formed like the heads of hellhounds, and they " +
             "are crafted from a minotaur.");
    add_id(({ "boots", "boots of the minotaur" }));
    add_property("tagged","hidden");
    set_type("boot");
    set_value(700);
    set_weight(1);
    set_ac(1);  
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
    set_wear_modifier("devotion_khorne", 10);
}

void on_wear(int silent, object obj) {
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->add_hook("__battack", store_fp("on_battack"));
    ply->add_hook("__attack", store_fp("on_attack"));
    if (!silent) {
        ply->command("growl");
    }
}

void on_remove(int silent) {
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__battack");
    ply->remove_hook("__attack");
}

int on_battack(object foe) {
    object ply;
    if (!objectp(ply = query_worn_by()) ||
        _next_attack < time()) 
    {
        return 0;
    }
    tell_object(ply, "You are recovering from the frenzy.\n");
    return 1;
}

void on_attack(object foe) {
    object ply, env;
    int time;
    if (!objectp(ply = query_worn_by()) ||
        !objectp(env = environment(ply)) ||
        env->query_property("no_special_attack") ||
        ply->query_busy_next_round() ||
        ply->query_tmp_prop("last_speed_attack") == time() ||
        ply->query_tmp_prop("devotion_khorne") < random(1000) ||
        !ply->do_attack(foe, this_object())) 
    {
        return;
    }
    tell_object(ply, bold("You feel the power of Khorne streaming through " +
                          "you, making your adrenaline pump wildly.\n"));
    tell_room(env, ply->query_name() + " suddenly goes into a frenzied " +
              "fury!\n", ({ ply }));
    ply->set_tmp_prop("last_speed_attack", time());
    if (!ply->is_chaos()) {
        _next_attack = time() + random(12);
    }
}

int query_extra_attack() {  
    return 2 + random(3);
}

