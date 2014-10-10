#include "/d/Empire/islands/dragon.h"

inherit EMP_I_ISLAND;

static void create() {
    ::create();
    set_map_file(DON_MAP);
    set_room_dir(DON_DIR_ROOMS);

    add_map_symbol(EMP_MAP_HILL,     "^");
    add_ansi_code (EMP_MAP_HILL,     "%^GREY%^");
    add_type_name (EMP_MAP_HILL,     "rough cave");

    add_map_symbol(EMP_MAP_MOUNTAIN, "#");
    add_ansi_code (EMP_MAP_MOUNTAIN, "%^GREY%^");
    add_type_name (EMP_MAP_MOUNTAIN, "cave wall");

    add_map_symbol(EMP_MAP_PLAIN,    ".");
    add_ansi_code (EMP_MAP_PLAIN,    "%^GREY%^");
    add_type_name (EMP_MAP_PLAIN,    "cave");

    add_type_name('O', "way out");
    add_type_name('D', "dragon's nest");

    add_road_type(EMP_MAP_HILL);
    add_road_type(EMP_MAP_PLAIN);
    add_block_type(EMP_MAP_MOUNTAIN);
}
