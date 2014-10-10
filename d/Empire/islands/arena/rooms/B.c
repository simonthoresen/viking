#include "/d/Empire/islands/arena.h"

inherit ARN_I_ROOM;

void create() {
    ::create();
    set_short("At the west exit");
    set_long("You are at the west exit.");
    add_exit(ARN_R_ARENA, "west");
}
