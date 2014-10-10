#include "/d/Empire/islands/ruins.h"

inherit EMP_I_ISLAND;

static void
create()
{
    ::create();
    set_map_file(RUN_MAP);
    set_room_dir(RUN_DIR_ROOMS);

    add_map_symbol(EMP_MAP_DESERT,    "/");
    add_ansi_code (EMP_MAP_DESERT,    "%^B_YELLOW%^%^RED%^");
    add_block_type(EMP_MAP_DESERT);

    add_map_symbol(EMP_MAP_LAVA,      "~");
    add_ansi_code (EMP_MAP_LAVA,      "%^B_RED%^%^L_RED%^");

    add_map_symbol(EMP_MAP_WATER,     "~");
    add_ansi_code (EMP_MAP_WATER,     "%^B_BLUE%^%^L_BLUE%^");

    add_type_name (RUN_MAP_AEGIR,     "statue of Aegir");
    add_type_name (RUN_MAP_FORNJOT,   "statue of Fornjot");
    add_type_name (RUN_MAP_KARI,      "statue of Kari");
    add_type_name (RUN_MAP_LOGI,      "statue of Logi");

    add_map_symbol(RUN_MAP_RUIN,      ".");
    add_ansi_code (RUN_MAP_RUIN,      "%^B_WHITE%^%^WHITE%^");
    add_type_name (RUN_MAP_RUIN,      "ruins");
    add_road_type (RUN_MAP_RUIN);

    add_type_name (RUN_MAP_RUNESTONE, "runestone");

    add_map_symbol(RUN_MAP_RUBBLE,    "\^");
    add_ansi_code (RUN_MAP_RUBBLE,    "%^B_GREY%^%^BLACK%^");
    add_type_name (RUN_MAP_RUBBLE,    "rubble");
    add_block_type(RUN_MAP_RUBBLE);

    add_map_symbol(RUN_MAP_WALL,      "#");
    add_ansi_code (RUN_MAP_WALL,      "%^B_RED%^%^RED%^");
    add_type_name (RUN_MAP_WALL,      "wall");
    add_block_type(RUN_MAP_WALL);
}
