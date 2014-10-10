#include "/d/Empire/islands/dragon.h"

inherit DON_I_ROOM;

void create() {
    ::create();
    set_short("Entrance to the Lair of Onyxia");
    set_long("You are at the entrance to the lair of the dragon queen " +
             "Onyxia. This is the way out! You should use it to get away " +
             "while you are still alive! An enormous cave lies beyond this " +
             "point, and it promises nothing but your own death.");
    add_exit("/d/Empire/var/islands/reikland/3/16", "out");
    add_property("no_wander");
}
