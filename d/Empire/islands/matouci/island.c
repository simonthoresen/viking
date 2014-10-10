#include "/d/Empire/islands/matouci.h"

inherit EMP_I_ISLAND;

void create() {
    ::create();
    set_map_file(MAT_MAP);
    set_room_dir(MAT_DIR_ROOMS);
    set_events_dir(MAT_DIR_EVENTS);
    set_event_time(15 * 60);

    add_map_symbol(EMP_MAP_FOREST,   "&");
    add_ansi_code (EMP_MAP_FOREST,   "%^B_GREEN%^%^GREEN%^");

    add_map_symbol(EMP_MAP_HILL,     "^");
    add_ansi_code (EMP_MAP_HILL,     "%^B_GREEN%^%^BLACK%^");

    add_map_symbol(EMP_MAP_MOUNTAIN, "^");
    add_ansi_code (EMP_MAP_MOUNTAIN, "%^B_GREY%^%^BOLD%^");
    add_block_type(EMP_MAP_MOUNTAIN);

    add_map_symbol(EMP_MAP_ROAD,     "/");
    add_ansi_code (EMP_MAP_ROAD,     "%^B_GREEN%^%^YELLOW%^");
    
    add_type_name('A', "way out");
    add_type_name('B', "way out");
    add_type_name('R', "cabin");
    add_type_name('S', "pit");
}
