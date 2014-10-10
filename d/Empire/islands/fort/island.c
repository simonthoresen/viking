#include "/d/Empire/islands/fort.h"

inherit EMP_I_ISLAND;

static void
create()
{
    int val;
    ::create();
    set_map_file(FOR_MAP);
    set_room_dir(FOR_DIR_ROOMS);

    add_map_symbol(EMP_MAP_FOREST, "&");
    add_ansi_code (EMP_MAP_FOREST, "%^B_GREEN%^%^L_GREEN%^");
    add_block_type(EMP_MAP_FOREST);

    add_map_symbol(EMP_MAP_PLAIN,  "/");
    add_ansi_code (EMP_MAP_PLAIN,  "%^B_GREEN%^%^GREEN%^");
    add_road_type (EMP_MAP_PLAIN);

    add_map_symbol(EMP_MAP_ROAD,   "/");
    add_ansi_code (EMP_MAP_ROAD,   "%^B_GREY%^%^BOLD%^");
    add_road_type (EMP_MAP_ROAD);

    add_type_name ('A', "goblin entry");
    add_map_symbol('a', "/");
    add_ansi_code ('a', "%^B_GREY%^%^BOLD%^");
    add_type_name ('a', "goblin hallway");
    add_road_type ('a');
    add_type_name ('B', "goblin throne");

    add_type_name ('C', "orc entry");
    add_map_symbol('c', "/");
    add_ansi_code ('c', "%^B_GREY%^%^BOLD%^");
    add_type_name ('c', "orc hallway");
    add_road_type ('c');
    add_type_name ('D', "orc throne");

    add_type_name ('E', "troll entry");
    add_map_symbol('e', "/");
    add_ansi_code ('e', "%^B_GREY%^%^BOLD%^");
    add_type_name ('e', "troll hallway");
    add_road_type ('e');
    add_type_name ('F', "troll throne");

    add_type_name ('G', "ogre entry");
    add_map_symbol('g', "/");
    add_ansi_code ('g', "%^B_GREY%^%^BOLD%^");
    add_type_name ('g', "ogre hallway");
    add_road_type ('g');
    add_type_name ('H', "ogre throne");

    add_map_symbol('w', "#");
    add_ansi_code ('w', "%^B_RED%^%^RED%^");
    add_type_name ('w', "wall");
    add_block_type('w');

    set_view_cols(15);
    set_view_rows(7);
}
