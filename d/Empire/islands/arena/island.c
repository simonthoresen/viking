#include "/d/Empire/islands/arena.h"

inherit EMP_I_ISLAND;

void create() {
    ::create();
    set_map_file(ARN_MAP);
    set_room_dir(ARN_DIR_ROOMS);

    add_block_type(ARN_MAP_WALL);
    add_map_symbol(ARN_MAP_WALL,    "#");
    add_ansi_code (ARN_MAP_WALL,    "%^B_RED%^%^RED%^");
    add_type_name (ARN_MAP_WALL,    "wall");

    add_map_symbol(EMP_MAP_FOREST,  ".");
    add_ansi_code (EMP_MAP_FOREST,  "%^B_GREY%^%^GREY%^");
    add_type_name (EMP_MAP_FOREST,  "arena");

    add_block_type(EMP_MAP_ROAD);
    add_map_symbol(EMP_MAP_ROAD,    ".");
    add_ansi_code (EMP_MAP_ROAD,    "%^B_BLACK%^%^BLACK%^");
    add_type_name (EMP_MAP_ROAD,    "road");

    add_ansi_code (EMP_MAP_DEFAULT, "%^B_BLUE%^");
    
    add_type_name('A', "way out");
    add_type_name('B', "way out");
    add_type_name('C', "way out");
    add_type_name('D', "way out");

    set_view_cols(15);
    set_view_rows(7);

    add_hook("__enter_inv", store_fp("enter_arena"));
}

void enter_arena(object ply, object env, object from) {
    if (!objectp(ply)) {
        return;
    }
    if (!objectp(present(ARN_C_FAILSAFE, ply))) {
        make(ARN_C_FAILSAFE, ply);
    }
}

void broadcast(string msg) {
    message("channels", "[Arena] " + msg, query_livings() + 
            ({ ARN_R_LOUNGE, ARN_R_ARENA }));
}
