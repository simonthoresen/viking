#include "/d/Empire/empire.h"

inherit EMP_I_ISLAND_CRITTERS;

static void create() {
    ::create();
    add_block_type(EMP_MAP_VOID);

    add_type_name(EMP_MAP_COAST,    "coast");
    add_type_name(EMP_MAP_DESERT,   "desert");
    add_type_name(EMP_MAP_FOREST,   "forest");
    add_type_name(EMP_MAP_HILL,     "hill");
    add_type_name(EMP_MAP_JUNGLE,   "jungle");
    add_type_name(EMP_MAP_LAVA,     "pool of lava");
    add_type_name(EMP_MAP_MOUNTAIN, "mountain");
    add_type_name(EMP_MAP_PLAIN,    "plain");
    add_type_name(EMP_MAP_ROAD,     "road");
    add_type_name(EMP_MAP_SWAMP,    "swamp");
    add_type_name(EMP_MAP_TUNDRA,   "tundra");
    add_type_name(EMP_MAP_VOID,     "void");
    add_type_name(EMP_MAP_WATER,    "body of water");
}
