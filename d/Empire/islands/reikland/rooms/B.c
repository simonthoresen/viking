#include "/d/Empire/islands/reikland.h"

inherit EMP_DIR_STD + "map_m";

static void create() {
    ::create();
    add_exit("/d/Empire/islands/blackrock/rooms/entry", "blackrock");
}
