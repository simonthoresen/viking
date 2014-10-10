#include "/d/Empire/empire.h"

inherit EMP_DIR_STD + "map_r";

static void create() {
    ::create();
    add_exit(EMP_DIR_VAR_ISLANDS + "reikland/39/36", "south");
}
