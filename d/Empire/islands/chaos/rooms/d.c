#include "/d/Empire/islands/chaos.h"

inherit EMP_DIR_STD + "map_d";

void create() {
    ::create();
    add_property("no_telein");
}
