#include "/d/Empire/islands/arena.h"

inherit ARN_I_ROOM;

void create() {
    ::create();
    set_short("At the east exit");
    set_long("You are at the east exit.");
    add_exit(ARN_R_ARENA, "east");
}
