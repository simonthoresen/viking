#include "/d/Empire/islands/chaos.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("The void");
    set_long("You are in the void.");
    add_property(({ "no_telein", "no_wander" }));
    add_hook("__enter_inv", store_fp("on_enter_inv"));
}

void on_enter_inv(object obj, object from) {
    if (!can_fly(obj)) {
        call_out("init_falling", 0, obj);
    }
}

void init_falling(object obj) {
    if (!objectp(obj) || !objectp(present(obj))) {
        return;
    }
    if (living(obj)) {
        obj->move_player("down", new(CAS_R_FALLING), 1);
    } else {
        obj->move(CAS_R_FALLING->query_landing());
    }
}
