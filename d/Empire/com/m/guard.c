#include "/d/Empire/empire.h"

#define P_GUARDS ("emp_guards")

inherit CMD_MODULE;

private string query_dir(object env, object ply) {
    mapping dat;
    string *arr;
    int i, len;
    if (!objectp(env) || !objectp(ply) ||
	!mapp(dat = env->query_property(P_GUARDS)))
    {
	return 0;
    }
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
	if (dat[arr[i]] == ply) {
	    return arr[i];
	}
    }
    return 0;
}

private object query_guard(object env, string dir) {
    mapping dat;
    if (!objectp(env) ||
	!mapp(dat = env->query_property(P_GUARDS)))
    {
	return 0;
    }
    return dat[dir];    
}

private void add_guard(object env, string dir, object ply) {
    mapping dat;
    if (!objectp(env) || !stringp(dir) || !objectp(ply)) {
	return;
    }
    if (!mapp(dat = env->query_property(P_GUARDS))) {
	dat = ([ ]);
	env->add_hook("__bperform_move", store_fp("check_guard"));
    }
    dat[dir] = ply;
    env->add_property(P_GUARDS, dat);
}

private void remove_guard(object env, string dir) {
    mapping dat;
    if (!objectp(env) || !stringp(dir)) {
	return;
    }
    if (!mapp(dat = env->query_property(P_GUARDS))) {
	return;
    }
    dat[dir] = 0;
    if (map_sizeof(dat) > 0) {
	env->add_property(P_GUARDS, dat);
    } else {
	env->remove_property(P_GUARDS);
	env->remove_hook("__bperform_move");
    }
}

private int stop_guard(object env, object ply) {
    string dir;
    if (stringp(dir = query_dir(env, ply))) {
	remove_guard(env, dir);
    }
    if (objectp(ply)) {
	ply->remove_hook("__move");
	ply->remove_hook("__short");
    }
    if (stringp(dir) && objectp(ply)) {
	tell_object(ply, "You stop guarding the " + dir + " exit.\n");
    }
    if (stringp(dir) && objectp(ply) && objectp(env)) {
	tell_room(env, ply->query_name() + " stops guarding the " + 
		  dir + " exit.\n", ({ ply }));
    }
    return stringp(dir);
}

private int start_guard(object env, string dir, object ply) {
    object guard;
    stop_guard(env, ply);
    if (objectp(guard = query_guard(env, dir))) {
	return notify_fail(guard->query_name() + " is already guarding the " + 
			   dir + " exit.");
    }
    add_guard(env, dir, ply);
    tell_object(ply, "You start guarding the " + dir + " exit.\n");
    tell_room(env, ply->query_name() + " starts guarding the " + dir + 
	      " exit.\n", ({ ply }));
    ply->add_hook("__move", store_fp("break_guard"));
    ply->add_hook("__short", store_fp("desc_guard"), dir);
    return 1;
}

public int main(string arg) {
    object ply, env;
    if (!objectp(ply = this_player()) || 
	!objectp(env = environment(ply)) ||
	!env->is_empire()) 
    {
	return 0;
    }
    if (!stringp(arg)) {
	if (stop_guard(env, ply)) {
	    return 1;
	}
	return notify_fail("Guard what exit?");
    }
    if (!stringp(env->query_exit(arg))) {
	return notify_fail("There is no such exit!");
    }
    return start_guard(env, arg, ply);
}

public string desc_guard(string dir) {
    return " (guarding the " + dir + " exit)";
}

public int break_guard(object from, object to) {
    stop_guard(from, previous_object());
    return 0;
}

public int check_guard(string dir, string to) {
    object ply, foe, env;
    int ply_str, foe_str;
    if (!objectp(ply = this_player()) || 
	!objectp(env = previous_object()) || 
	!objectp(foe = query_guard(env, dir)))
    {
	return 0;
    }
    if (!objectp(present(foe, env))) {
	stop_guard(env, foe);
	return 0; /* _P_A_R_A_N_O_I_A_ */
    }
    if (ply == foe) {
	return 0;
    }
    if (!interactive(foe)) {
        foe->do_attack(ply);
    }
    ply_str = ply->query_str();
    foe_str = foe->query_str();
    if (ply->query_busy_next_round() ||
	foe_str + random(foe_str) < ply_str + random(ply_str)) 
    {
	tell_object(ply, bold(foe->query_name() + " tries to stop you, but " +
			      "you push your way " + dir + ".\n"));
	tell_object(foe, bold("You try to stop " + ply->query_name() + ", " +
			      "but " + ply->query_pronoun() + " pushes " + 
			      ply->query_objective() + " way " + dir + ".\n"));
	tell_room(env, foe->query_name() + " tries to stop " + 
		  foe->query_name() + ", but " + ply->query_pronoun() + 
		  "pushes " + ply->query_objective() + " way " + dir + ".\n", 
		  ({ foe, ply }));
	return 0;
    }
    tell_object(ply, bold("You try to go " + dir + ", but " + 
			  foe->query_name() + " pushes you back!\n"));
    tell_object(foe, bold(ply->query_name() + " tries to go " + dir + 
			  ", but you push " + ply->query_objective() + 
			  " back!\n"));
    tell_room(env, ply->query_name() + " tries to go " + dir + 
	      ", but " + foe->query_name() + " pushes " + 
	      ply->query_objective() + " back.\n", ({ foe, ply }));
    ply->set_busy_next_round();
    return 1;
}

public string short_help() {
    return "Prevent anyone from moving through an exit.\n";
}
