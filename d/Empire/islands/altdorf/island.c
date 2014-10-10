#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ISLAND;

private int _time;

static void create() {
    ::create();
    _time = EMP_D_TIME->query_hour_of_day();

    set_map_file(ALT_MAP);
    set_room_dir(ALT_DIR_ROOMS);
    set_events_dir(ALT_DIR_EVENTS);

    add_road_type(EMP_MAP_ROAD);
    add_road_type(EMP_MAP_JUNGLE);
    add_road_type(ALT_MAP_BRIDGE);
    add_road_type(ALT_MAP_AMTSBEZIRK);
    add_road_type(ALT_MAP_BANKBEZIRK);
    add_road_type(ALT_MAP_REIKERBAHN);

    add_map_symbol(ALT_MAP_BRIDGE,     "/");
    add_ansi_code (ALT_MAP_BRIDGE,     "%^B_GREY%^%^BLUE%^");
    add_type_name (ALT_MAP_BRIDGE,     "bridge");

    add_block_type(ALT_MAP_CITYWALL);
    add_map_symbol(ALT_MAP_CITYWALL,   "#");
    add_ansi_code (ALT_MAP_CITYWALL,   "%^B_RED%^%^RED%^");
    add_type_name (ALT_MAP_CITYWALL,   "citywall");

    add_map_symbol(ALT_MAP_AMTSBEZIRK, "/");
    add_ansi_code (ALT_MAP_AMTSBEZIRK, "%^B_GREY%^%^L_GREY%^");
    add_type_name (ALT_MAP_AMTSBEZIRK, "district called Amtsbezirk");

    add_map_symbol(ALT_MAP_BANKBEZIRK, "/");
    add_ansi_code (ALT_MAP_BANKBEZIRK, "%^B_GREY%^%^L_GREY%^");
    add_type_name (ALT_MAP_BANKBEZIRK, "district called Bankbezirk");

    add_map_symbol(ALT_MAP_REIKERBAHN, "/");
    add_ansi_code (ALT_MAP_REIKERBAHN, "%^B_GREY%^%^L_GREY%^");
    add_type_name (ALT_MAP_REIKERBAHN, "slum called Reikerbahn");

    add_map_symbol(EMP_MAP_ROAD,       "/");
    add_ansi_code (EMP_MAP_ROAD,       "%^B_GREY%^%^L_GREY%^");
    add_type_name (EMP_MAP_ROAD,       "road");

    add_block_type(EMP_MAP_MOUNTAIN);
    add_map_symbol(EMP_MAP_MOUNTAIN,   "#");
    add_ansi_code (EMP_MAP_MOUNTAIN,   "%^B_YELLOW%^%^RED%^");
    add_type_name (EMP_MAP_MOUNTAIN,   "building");

    add_map_symbol(EMP_MAP_COAST,      "c");
    add_ansi_code (EMP_MAP_COAST,      "%^B_CYAN%^%^CYAN%^");
    add_type_name (EMP_MAP_COAST,      "riverbank");

    add_map_symbol(EMP_MAP_FOREST,     "&");
    add_ansi_code (EMP_MAP_FOREST,     "%^B_GREEN%^%^L_GREEN%^");

    add_map_symbol(EMP_MAP_JUNGLE,     "/");
    add_ansi_code (EMP_MAP_JUNGLE,     "%^B_GREY%^%^GREEN%^");
    add_type_name (EMP_MAP_JUNGLE,     "park");

    add_map_symbol(EMP_MAP_PLAIN,      "/");
    add_ansi_code (EMP_MAP_PLAIN,      "%^B_GREEN%^%^GREEN%^");

    add_map_symbol(EMP_MAP_SWAMP,      "/");
    add_ansi_code (EMP_MAP_SWAMP,      "%^B_CYAN%^%^BLUE%^");

    add_map_symbol(EMP_MAP_WATER,      "~");
    add_ansi_code (EMP_MAP_WATER,      "%^B_BLUE%^%^BLUE%^");
    add_type_name (EMP_MAP_WATER,      "river");
    
    add_type_name('A', "armour smithy");
    add_type_name('C', "shop");
    add_type_name('D', "dock");
    add_type_name('F', "bank");
    add_type_name('G', "barracks");
    add_type_name('H', "administrative building");
    add_type_name('I', "artificer");
    add_type_name('L', "tavern");
    add_type_name('O', "hospital");
    add_type_name('P', "post office");
    add_type_name('R', "apothecary");
    add_type_name('T', "temple");
    add_type_name('W', "weapon smithy");
        
    set_view_cols(15);
    set_view_rows(7);

    add_hook("__heart_beat", store_fp("city_noise"));

    set_num_critters(20);
    add_critter(ALT_C_COMMONER);
    add_critter(ALT_C_GUARD);
    add_critter(ALT_C_WATCHMAN);
}

public string query_random_event(object ply, object env) {
    if (!is_road(env)) {
        return 0;
    }
    return ::query_random_event(ply, env);
}

public object *find_guards() {
    return filter_array(query_livings(), "call_other_true", 
			FILTER_OB, "is_guard");
}

static void city_noise() {
    int val;
    if ((val = EMP_D_TIME->query_hour_of_day()) != _time) {
	tell_nearby(18, 17, 15, "The bells of town hall chime " + 
		    EMP_D_TIME->query_stime() + " from the #d.\n");
	filter_array(query_livings(), "call_other_true", FILTER_OB, 
		     "is_watchman")->yell_time(val);
	_time = val;
    }
    switch (random(50)) {
    case 0:
	/* Dalbran Fellhammer's [A]rmour Smithy */
	tell_nearby(9, 57, 5, "*CLANK* You hear metal being worked to the " +
		    "#d.\n");
	break;
    case 1:
	/* Reik-Talabec Trading [C]ompany */
	tell_nearby(10, 46, 5, "You hear someone haggling over prices " +
		    "to the #d.\n");
	break;
    case 2:
	/* The Niederhafen [D]ocks */
	tell_nearby(16, 40, 5, "A boat blows its horn as it arrives at " +
		    "the docks to the #d.\n");
	break;
    case 3:
	/* Association of [F]inanciers and Moneylenders */
	tell_nearby(19, 19, 5, "You hear someone discussing interest rates " +
		    "to the #d.\n");
	break;
    case 4:
	/* Imperial [G]uard barracks and armoury */
	tell_nearby(27, 25, 5, "You hear someone do a roll call to the #d.\n");
	break;
    case 5:
	/* The People's [H]all */
	tell_nearby(21, 18, 5, "There is a lot of commotion to the #d.\n");
	break;
    case 6:
	/* Hart's [L]odge */
	tell_nearby(29, 40, 5, "You hear songs and laughter from the #d.\n");
	break;
    case 7:
	/* H[O]spice Priory of Shallya */
	tell_nearby(25, 36, 5, "You hear moans and wimpers to the #d.\n");
	break;
    case 8:
	/* The Imperial [P]ostal Service */
	tell_nearby(5, 36, 5, "A pigeon flies overhead towards the #d.\n");
	break;
    case 9:
	/* Krank's Potions and [R]emedies */
	tell_nearby(10, 34, 5, "The pugent stench of ammonia seeps in from " +
		    "the #d.\n");
	break;
    case 10:
	/* Great [T]emple and Cathedral of Sigmar */
	tell_nearby(24, 28, 5, "You hear the chanting of monks from the #d.\n");
	break;
    case 11:
	/* Tots Blatter's [W]eapon Smithy */
	tell_nearby(7, 50, 5, "*CLANK* You hear metal being worked to the " +
		    "#d.\n");
	break;
    }
}
