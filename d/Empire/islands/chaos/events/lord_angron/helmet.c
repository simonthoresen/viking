#include "/d/Empire/empire.h"

inherit I_ARMOUR;

void create() {
    ::create();
    set_name("Helmet of Skulls");
    set_short("a helmet with the shape of a human skull");
    set_long("The helmet has engraved several symbols of Khorne. In it's " +
	     "forehead you see a skull engraved.\n");
    add_property(({ "iron", "tagged", "hidden" }));
    set_value(500);
    set_weight(1);
    set_ac(1);
    set_type("helmet");
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
    set_wear_modifier("devotion_khorne", 10);
}  

void on_wear(int silent, object obj) {
    object ply;
    if (!objectp(ply = query_worn_by())) {
	return;
    }
    tell_object(ply, "You want to give someone a bad headache.\n");
    ply->add_hook("__fight_beat", store_fp("on_fight_beat"));
}

void on_remove(int silent) {
    object ply;
    if (!objectp(ply = query_worn_by())) {
	return;
    }
    ply->remove_hook("__fight_beat");
}

void on_fight_beat(object foe) {
    object ply, env;
    if (!objectp(ply = query_worn_by()) ||
	!objectp(env = environment(ply)) ||
	env->query_property("no_special_attack") ||
	random(100) > 10)
    {
	return;
    }
    tell_object(ply, "You grab " + foe->query_name() + " by the neck!\n");
    tell_object(foe, ply->query_name() + " grabs you by the neck!\n");
    tell_room(env, ply->query_name() + " grabs " + foe->query_name() + 
	      " by the neck.\n", ({ ply, foe }));
    ply->do_attack(foe, this_object());
}

int query_damage() { 
    object ply;
    if (!objectp(ply = query_worn_by())) {
	return 0;
    }
    return random(ply->query_str() / 2) +
  	   random(ply->query_dex() / 2) + 
	   random(ply->query_tmp_prop("devotion_khorne")); 
}

string query_damage_type() { 
    return "blunt"; 
}

int query_extra_attack() { 
    return 1; 
}

void damage_done(int dmg, object foe) {
    object ply;
    if (!objectp(ply = query_worn_by())) {
	return;
    }
    MESSAGE_D->weapon_noise(foe, dmg, "blunt", ply);
}
