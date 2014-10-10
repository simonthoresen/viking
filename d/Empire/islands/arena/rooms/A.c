#include "/d/Empire/islands/arena.h"

inherit ARN_I_ROOM;

void create() {
    ::create();
    set_short("At the north exit");
    set_long("You are at the north exit.");
    add_exit(ARN_R_ARENA, "north");
}
