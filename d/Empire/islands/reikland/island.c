#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ISLAND;

void create() {
    ::create();
    set_map_file(RED_MAP);
    set_room_dir(RED_DIR_ROOMS);
    set_events_dir(RED_DIR_EVENTS);

    set_view_cols(16);
    set_view_rows(8);

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
    
    add_type_name('A', "city");
    add_type_name('B', "blackrock");
    add_type_name('C', "clearing");
    add_type_name('D', "cave");
    add_type_name('F', "fort");
    add_type_name('R', "ruins");
    
    set_num_critters(75);
}

public string query_random_critter(object env) {
    if (!objectp(env)) {
        return 0;
    }
    switch (env->query_map_type()) {
    case EMP_MAP_COAST:
    case EMP_MAP_SWAMP:
    case EMP_MAP_WATER:
        switch (random(4)) {
        case 0: return RED_DIR_OBJ + "alligator";
        case 1: return RED_DIR_OBJ + "crocodile";
        case 2: return RED_DIR_OBJ + "frog";
        case 3: return RED_DIR_OBJ + "turtle";
        }
    case EMP_MAP_DESERT:
        switch (random(8)) {
        case 0: return RED_DIR_OBJ + "black_panther";
        case 1: return RED_DIR_OBJ + "panther";
        case 2: return RED_DIR_OBJ + "possum";
        case 3: return RED_DIR_OBJ + "racoon";
        case 4: return RED_DIR_OBJ + "rat";
        case 5: return RED_DIR_OBJ + "rodent";
        case 6: return RED_DIR_OBJ + "snake";
        case 7: return RED_DIR_OBJ + "spider";
        }
    case EMP_MAP_FOREST:
        switch (random(7)) {
        case 0: return RED_DIR_OBJ + "fly"; 
        case 1: return RED_DIR_OBJ + "goblin";
        case 2: return RED_DIR_OBJ + "goblin_boss";
        case 3: return RED_DIR_OBJ + "deer";
        case 4: return RED_DIR_OBJ + "owl";
        case 5: return RED_DIR_OBJ + "rabbit";
        case 6: return RED_DIR_OBJ + "squirrel";
        }
    case EMP_MAP_HILL:
        switch (random(4)) {
        case 0: return RED_DIR_OBJ + "bear";
        case 1: return RED_DIR_OBJ + "beetle";
        case 2: return RED_DIR_OBJ + "buck";
        case 3: return RED_DIR_OBJ + "bat";
        }
    case EMP_MAP_MOUNTAIN: 
        switch (random(4)) {
        case 0: return RED_DIR_OBJ + "cavebat";
        case 1: return RED_DIR_OBJ + "brown_bear";
        case 2: return RED_DIR_OBJ + "panda_bear";
        case 3: return RED_DIR_OBJ + "troll";
        }
    case EMP_MAP_JUNGLE:
        switch (random(4)) {
        case 0: return RED_DIR_OBJ + "bee";
        case 1: return RED_DIR_OBJ + "butterfly";
        case 2: return RED_DIR_OBJ + "parrot";
        case 3: return RED_DIR_OBJ + "peacock";
        }
    case EMP_MAP_PLAIN:
        switch (random(5)) {
        case 0: return RED_DIR_OBJ + "bird";
        case 1: return RED_DIR_OBJ + "bunny";
        case 2: return RED_DIR_OBJ + "grasshopper";
        case 3: return RED_DIR_OBJ + "sheep";
        case 4: return RED_DIR_OBJ + "wasp";
        }
    case EMP_MAP_TUNDRA:
        switch (random(9)) {
        case 0: return RED_DIR_OBJ + "ghoul";
        case 1: return RED_DIR_OBJ + "beastman";
        case 2: return RED_DIR_OBJ + "black_spider";
        case 3: return RED_DIR_OBJ + "bone_worm";
        case 4: return RED_DIR_OBJ + "fimir";
        case 5: return RED_DIR_OBJ + "skeleton";
        case 6: return RED_DIR_OBJ + "slug";
        case 7: return RED_DIR_OBJ + "wolf";
        case 8: return RED_DIR_OBJ + "zombie";
        }
    }
    return 0;
}

