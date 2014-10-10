#include "/d/Empire/islands/dragon.h"

inherit DON_I_ROOM;

static void create() {
    ::create();
    set_short("The heart of Onyxia's lair");
    set_long("You have come to the heart of Onyxia's lair. This is where " +
             "the dragon queen sleeps. The ground here is warm, but yet " +
             "foreboding. This is NOT where you want to be! Get out while " +
             "you still can!");
    if (sscanf(source_file_name(), EMP_DIR_VAR + "%*s")) {
        add_hook("__reset", store_fp("maybe_spawn"));
    }
}

public void maybe_spawn(int flag) {
    object obj;
    if (!objectp(obj = DON_D_DRAGON->create_dragon())) {
	return;
    }
    obj->move_player("ignored", this_object());
}
