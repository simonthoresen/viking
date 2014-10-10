#include "/d/Empire/empire.h"

inherit base CMD_MODULE;
inherit util EMP_I_UTIL;

static void create() {
    base::create();
    util::create();
}

static int main(string arg) {
    object ply, island;
    string file, *map;
    if (!objectp(ply = this_player())) {
	return 0;
    }
    if (!stringp(arg) || !strlen(arg = getopts("ac", arg))) {
        if (!stringp(file = environment(ply)->query_island())) {
            return notify_fail("Usage: " + query_verb() + " <island>");
        }
        sscanf(file, EMP_DIR_ISLANDS + "%s/island", arg);
    } else {
        file = EMP_DIR_ISLANDS + arg + "/island";
    }
    if (file_size(file + ".c") < 0 ||
        !objectp(island = file->__bootstrap()) ||
	!arrayp(map = island->create_island_view()))
    {
        return notify_fail("Island '" + file + "' not found.");
    }
    if (opts['a']) {
	map = island->format_view(map, 1);
    } else if (opts['c']) {
	map = island->format_view(map, store_fp("do_unload"), arg);
    } else {
	map = island->format_view(map, store_fp("is_loaded"), arg);
    }
    tell_ansi(ply, "\n" + implode(map, "\n"));
    return 1;
}

public int is_loaded(int row, int col, int type, string island) {
    return objectp(find_object(EMP_DIR_VAR_ISLANDS + island + 
			       "/" + row + "/" + col));
}

public int do_unload(int row, int col, int type, string island) {
    object env;
    if (!objectp(env = find_object(EMP_DIR_VAR_ISLANDS + island + 
                                   "/" + row + "/" + col))) 
    {
        return 0;
    }
    destruct(env);
    return 1;
}

public string short_help() {
    return "Prints a map of the loaded rooms of an island.";
}
