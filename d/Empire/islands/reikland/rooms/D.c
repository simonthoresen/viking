#include "/d/Empire/islands/reikland.h"

inherit EMP_DIR_STD + "map_m";

static void create() {
    ::create();
    add_exit("/d/Empire/var/islands/dragon/36/30", "lair");
}
