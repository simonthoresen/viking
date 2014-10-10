#include "/d/Empire/islands/arena.h"

inherit I_MONSTER;

void create() {
    ::create();
    set_name("bee");
    set_short(0);
    set_long("It is a busy little bee.");
    add_property(({ "no_nothing", EMP_P_IGNORE }));
    add_hook("__bnotify_attack", store_fp("on_bnotify_attack"));
    add_hook("__bdie", store_fp("on_bdie"));
    add_hook("__catch_tell", store_fp("on_catch_tell"));
    invis();
}

int on_bnotify_attack(object foe) {
    return 1;
}

int on_bdie(object foe) {
    return 1;
}

void on_catch_tell(string msg) {
    receive_message("", msg);
}

void receive_message(mixed class, string msg) {
    object env;
    if (!objectp(env = environment())) {
	return;
    }
    message(class, sprintf("[%2d, %2d]: %s", env->query_map_row(),
			   env->query_map_col(), msg),
	    ARN_R_LOUNGE->__bootstrap());
    /* block ::receive_message() as it will call __catch_tell */
}
