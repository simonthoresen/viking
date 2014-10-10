#include "/d/Empire/empire.h"

inherit I_ARMOUR;

void create() {
    ::create();
    set_name("Gauntlets of Khorne");
    set_short("a pair of gauntlets");
    set_long("This pair of gauntlets has a large red symbol on each fist.");
    set_type("glove");
    add_id(({ "gauntlets", "gloves" }));
    add_property(({ "iron", "tagged", "hidden" }));
    set_value(1000);
    set_weight(1);
    set_ac(1);  
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
}  

void on_wear(int silent, object obj) {
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    tell_object(ply, "You feel more like a fighter now.\n");
    ply->add_hook("__fight_beat", store_fp("on_fight_beat"));
}

void on_remove(int silent) {
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    tell_object(ply, "You feel like a wuss again.\n");
    ply->remove_hook("__fight_beat");
}

void on_fight_beat(object foe) {
    object ply, env;
    int lhs, rhs;
    if (!objectp(ply = query_worn_by()) ||
	!objectp(env = environment(ply)) ||
	env->query_property("no_special_attack")) 
    {
        return;
    }
    lhs = objectp(ply->query_weapon(1));
    rhs = objectp(ply->query_weapon(2)) || 
	  objectp(ply->query_worn_armour("shield"));
    if (lhs && rhs) {
	if (random(100) > 10) {
	    return;
	}
    } else if (lhs || rhs) {
	if (random(100) > 25) {
	    return;
	}
    } else {
	if (random(100) > 50) {
	    return;
	}
    }
    tell_object(ply, "You punch " + foe->query_name() + "!\n");
    EMP_D_COMBAT->hit_player(ply, foe, random(ply->query_str()) +
			     random(ply->query_tmp_prop("devotion_khorne")), 
			     "impact", 0, "fist");
}
