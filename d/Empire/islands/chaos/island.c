#include "/d/Empire/islands/chaos.h"

inherit EMP_I_ISLAND;

static void
create()
{
    ::create();
    set_map_file(CAS_MAP);
    set_room_dir(CAS_DIR_ROOMS);
    set_events_dir(CAS_DIR_EVENTS);

    set_view_cols(16);
    set_view_rows(8);

    add_road_type(EMP_MAP_DESERT);

    add_map_symbol(EMP_MAP_DESERT, "X");
    add_ansi_code (EMP_MAP_DESERT, "%^B_YELLOW%^%^YELLOW%^");

    add_map_symbol(EMP_MAP_LAVA,   "~");
    add_ansi_code (EMP_MAP_LAVA,   "%^B_RED%^%^RED%^");

    add_map_symbol(EMP_MAP_WATER,  " ");
    add_ansi_code (EMP_MAP_WATER,  "%^B_BLACK%^%^BLACK%^");
    add_type_name (EMP_MAP_WATER,  "void");

    add_type_name('P', "portal");

    set_num_critters(15);
    add_critter(CAS_DIR_OBJ + "hound");
    add_critter(CAS_DIR_OBJ + "imp");
    add_critter(CAS_DIR_OBJ + "mage");
    add_critter(CAS_DIR_OBJ + "warrior");
}
