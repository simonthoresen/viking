#include "/d/Empire/islands/artifact.h"

inherit EMP_I_ISLAND;

static void
create()
{
    ::create();
    set_map_file(ATI_MAP);
    set_room_dir(ATI_DIR_ROOMS);

    add_map_symbol(EMP_MAP_COAST,    "c");
    add_ansi_code (EMP_MAP_COAST,    "%^B_CYAN%^%^CYAN%^");
    add_road_type (EMP_MAP_COAST);

    add_map_symbol(EMP_MAP_DESERT,   "/");
    add_ansi_code (EMP_MAP_DESERT,   "%^B_YELLOW%^%^RED%^");
    add_road_type (EMP_MAP_DESERT);

    add_map_symbol(EMP_MAP_FOREST,   "&");
    add_ansi_code (EMP_MAP_FOREST,   "%^B_GREEN%^%^GREY%^");
    add_road_type (EMP_MAP_FOREST);

    add_map_symbol(EMP_MAP_HILL,     "\^");
    add_ansi_code (EMP_MAP_HILL,     "%^B_GREY%^%^BOLD%^");
    add_road_type (EMP_MAP_HILL);

    add_map_symbol(EMP_MAP_JUNGLE,   "@");
    add_ansi_code (EMP_MAP_JUNGLE,   "%^B_GREEN%^%^L_GREEN%^");
    add_road_type (EMP_MAP_JUNGLE);

    add_map_symbol(EMP_MAP_LAVA,     "~");
    add_ansi_code (EMP_MAP_LAVA,     "%^B_RED%^%^L_RED%^");

    add_map_symbol(EMP_MAP_MOUNTAIN, "\^");
    add_ansi_code (EMP_MAP_MOUNTAIN, "%^B_GREY%^%^BLACK%^");
    add_road_type (EMP_MAP_MOUNTAIN);

    add_map_symbol(EMP_MAP_PLAIN,    "/");
    add_ansi_code (EMP_MAP_PLAIN,    "%^B_YELLOW%^%^GREEN%^");
    add_road_type (EMP_MAP_PLAIN);

    add_map_symbol(EMP_MAP_ROAD,     ".");
    add_ansi_code (EMP_MAP_ROAD,     "%^B_YELLOW%^%^BLACK%^");

    add_map_symbol(EMP_MAP_SWAMP,    "~");
    add_ansi_code (EMP_MAP_SWAMP,    "%^B_YELLOW%^%^BLUE%^");
    add_road_type (EMP_MAP_SWAMP);

    add_map_symbol(EMP_MAP_TUNDRA,   "/");
    add_ansi_code (EMP_MAP_TUNDRA,   "%^B_GREY%^%^BOLD%^");
    add_road_type (EMP_MAP_TUNDRA);

    add_map_symbol(EMP_MAP_WATER,    "~");
    add_ansi_code (EMP_MAP_WATER,    "%^B_BLUE%^%^L_BLUE%^");
    add_block_type(EMP_MAP_WATER);

    add_type_name(ATI_MAP_GUILD,     "hut of enlightenment");
    add_type_name(ATI_MAP_POST,      "post office");
    add_type_name(ATI_MAP_SCORES,    "path of legends");
    add_type_name(ATI_MAP_SKILLS,    "tree of knowledge");
    add_type_name(ATI_MAP_SMITHY,    "anvil of Volund");
    add_type_name(ATI_MAP_SPELLS,    "oasis of magic");
}
