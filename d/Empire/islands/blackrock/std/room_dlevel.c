#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_ROOM_BASE;

static void create() {
    ::create();
    add_hook("__reset", store_fp("update_dlevel"));
}

static void update_dlevel(int flag) {
    int val;
    if (flag) {
        return;
    }
    val = 100 - (('z' - query_map_type()) * 100) / 25;
    add_property("dangerlevel", val < 0 ? 0 : (val < 100 ? val : 100));
}
