#include "/d/Empire/islands/matouci.h"

inherit EMP_DIR_STD + "map_r";

void create() {
    ::create();
    add_exit("/room/plane4", "west");
}
