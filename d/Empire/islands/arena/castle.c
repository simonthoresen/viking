#include "/d/Empire/islands/arena.h"

inherit I_OBJECT;

object _entry;

void create() {
    ::create();
    if (objectp(_entry = "/room/shop_adv_tunnel"->__bootstrap())) {
        _entry->add_exit(ARN_R_ARENA, "west");
        _entry->add_my_desc("There is an arena to the west.");
    }
}

void on_destruct() {
    ::on_destruct();
    if (objectp(_entry)) {
        _entry->remove_exit("west");
        _entry->remove_my_desc();
    }
}
