#include "/d/Empire/islands/reikland.h"

inherit EMP_DIR_STD + "map_d";

static void create() {
    ::create();
    set_long("The ruins of a city is being uncovered here.");
    /* add_exit("/d/Empire/islands/ruins/rooms/entry", "ruins"); */
}
