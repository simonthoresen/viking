#include "/d/Empire/islands/chaos.h"

inherit EMP_DIR_STD + "map_l";

void create() {
    ::create();
    add_property("no_telein");
}
