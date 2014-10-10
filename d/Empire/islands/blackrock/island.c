#include "/d/Empire/islands/blackrock.h"

inherit EMP_I_ISLAND;

static void
create() 
{
    int val;
    ::create();
    set_map_file(BRD_MAP);
    set_room_dir(BRD_DIR_ROOMS);
    if ((file_size(query_room(1, 1) + ".c")) > 0 &&
	(val = query_num_rows()) > 0 &&
	(val = val * query_num_cols(0)) > 0)
    {
	set_num_critters(max(1, val / 75));
    }
    add_critter(BRD_DIR_OBJ + "archon");
    add_critter(BRD_DIR_OBJ + "basilisk");
    add_critter(BRD_DIR_OBJ + "beholder");
    add_critter(BRD_DIR_OBJ + "death_knight");
    add_critter(BRD_DIR_OBJ + "devil");
    add_critter(BRD_DIR_OBJ + "drake");
    add_critter(BRD_DIR_OBJ + "efreet");
    add_critter(BRD_DIR_OBJ + "elemental");
    add_critter(BRD_DIR_OBJ + "gargoyle");
    add_critter(BRD_DIR_OBJ + "ghoul");
    add_critter(BRD_DIR_OBJ + "golem");
    add_critter(BRD_DIR_OBJ + "lich");
    add_critter(BRD_DIR_OBJ + "mind_flayer");
    add_critter(BRD_DIR_OBJ + "minotaur");
    add_critter(BRD_DIR_OBJ + "ooze");
    add_critter(BRD_DIR_OBJ + "skeleton");
    add_critter(BRD_DIR_OBJ + "wraith");
    
    for (val = 'a'; val <= 'z'; ++val) {
        add_map_symbol(val, "/");
        switch (val) {
        case 'a'..'e': add_ansi_code(val, "%^GREEN%^");    break;
        case 'f'..'i': add_ansi_code(val, "%^L_GREEN%^");  break;
        case 'j'..'m': add_ansi_code(val, "%^YELLOW%^");   break;
        case 'n'..'q': add_ansi_code(val, "%^L_YELLOW%^"); break;
        case 'r'..'u': add_ansi_code(val, "%^RED%^");      break;
        case 'v'..'z': add_ansi_code(val, "%^L_RED%^");    break;
        }
        add_type_name(val, "cave");
        add_road_type(val); 
    }

    add_map_symbol(BRD_MAP_ENTRY, "E");
    add_type_name (BRD_MAP_ENTRY, "way out");
    add_road_type (BRD_MAP_ENTRY);

    add_map_symbol(BRD_MAP_EXIT,  "X");
    add_type_name (BRD_MAP_EXIT,  "sanctum");
    add_road_type (BRD_MAP_EXIT);

    add_map_symbol(BRD_MAP_WALL,  "#");
    add_ansi_code (BRD_MAP_WALL,  "%^B_GREY%^%^GREY%^");
    add_type_name (BRD_MAP_WALL,  "wall");
    add_block_type(BRD_MAP_WALL);
}

public int
try_recreate(int delay) 
{
    if (objectp(present(BRD_C_KEEPER, BRD_R_ENTRY->__bootstrap()))) {
        return 0;
    }
    make(BRD_C_KEEPER, BRD_R_ENTRY)->count_down(delay);
    return 1;
}

public void
broadcast(string str) 
{
    message("channels", "[Blackrock]: " + str + "\n", 
	    query_livings() + ({ BRD_R_ENTRY->__bootstrap() }));
}

public object
create_random_critter(object env) 
{
    int val;
    object obj;
    if (!objectp(env) ||
        !objectp(obj = ::create_random_critter(env)))
    {
	return 0;
    }
    val = env->query_property("dangerlevel");
    if (val < 0) {
        val = 0;
    }
    if (val > 100) {
        val = 100;
    }
    obj->set_dangerlevel(val);
    make(BRD_C_COIN, obj)->add_amount(BRD_COIN_LOOT(val) - 1);
    return obj;
}

public string
find_entry() 
{
    return find_map_type(BRD_MAP_ENTRY);
}

public object
load_entry() 
{
    string str;
    if (!stringp(str = find_entry()) ||
	file_size(str + ".c") < 0) 
    {
	return 0;
    }
    return str->__bootstrap();
}
