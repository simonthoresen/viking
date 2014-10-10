#include "/d/Empire/islands/prison.h"

inherit EMP_I_ISLAND;

void create() {
    ::create();
    set_map_file(PRI_MAP);

    add_road_type (EMP_MAP_PLAIN);
    add_map_symbol(EMP_MAP_PLAIN,   "/");
    add_ansi_code (EMP_MAP_PLAIN,   "%^B_GREEN%^%^GREEN%^");
    add_type_name (EMP_MAP_PLAIN,   "plain");

    add_block_type(EMP_MAP_WATER);
    add_map_symbol(EMP_MAP_WATER,   "~");
    add_ansi_code (EMP_MAP_WATER,   "%^B_BLUE%^%^BLUE%^");
    add_type_name (EMP_MAP_WATER,   "water");
}
