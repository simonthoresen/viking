#include "/d/Empire/empire.h"

inherit CMD_MODULE;

private int wiz_main() {
    int *arr;
    arr = map_array(sort_array(filter_array(get_files(EMP_DIR_ISLANDS), 
                                            "is_island"), 
                               "cmp_island"), "main");
    if (sizeof(arr & ({ 1 })) == 0) {
        return notify_fail("No livings in Empire.");
    }
    return 1;
}

int main(string arg) {
    string file, line, col;
    object ply, *who;
    mapping dat;
    int i, len;
    if (!objectp(ply = this_player())) {
	return 0;
    }
    if (wizardp(ply) && !stringp(arg)) {
        return wiz_main();
    }
    if (!stringp(arg) || strlen(arg) == 0) {
        if (!stringp(file = environment(ply)->query_island())) {
            return notify_fail("Usage: " + query_verb() + " <island>");
        }
        sscanf(file, EMP_DIR_ISLANDS + "%s/island", arg);
    } else {
        file = EMP_DIR_ISLANDS + arg + "/island";
    }
    if (file_size(file + ".c") < 0) {
        return notify_fail("Island '" + arg + "' not found.");
    }
    if (!arrayp(who = file->query_livings()) ||
        (len = sizeof(who = filter_array(who, "is_player"))) == 0) 
    {
        return notify_fail("No livings on '" + arg + "'.");
    }
    who = sort_array(who, "cmp_living", this_object());
    if (mapp(dat = this_player()->query_property("COLOURS"))) {
        col = dat["whonames"];
    } else {
        col = 0;
    }
    line = sprintf("%'-'74s\n", "");
    write(line);
    write("There are " + len + " livings on '" + arg + "' at " + 
          ctime(time()) + "\n");
    write(line);
    for(i = 0; i < len; ++i) {
        object ply;
        string str;
        if (!objectp(ply = who[i])) {
            continue;
        }
        str = "/com/g/who"->prefix(ply);
        if (query_idle(ply) > 30) {
            str += "I ";
        } else {
            str += "  ";
        }
        str += ply->query_pre_title();
        if (stringp(col)) {
            str += col;
        }
        str += ply->query_name();
        if (stringp(col)) {
            str += "%^END%^";
        }
        str += " " + ply->query_title();
        write(str + "\n");
    }    
    write(line);
    return 1;
}

int is_island(string str) {
    return file_size(EMP_DIR_ISLANDS + str + "/island.c") > 0;
}

int is_player(object ply) {
    return objectp(ply) && interactive(ply);
}

int cmp_island(string lhs, string rhs) {
    return -strcmp(lhs, rhs);
}

int cmp_player(object lhs, object rhs) {
    if (lhs->query_level() > rhs->query_level()) {
        return -1;
    }
    if (lhs->query_level() < rhs->query_level()) {
        return 1;
    }
    if (lhs->query_name() < rhs->query_name()) {
        return -1;
    }
    return 0;
}

string short_help() {
    return "Prints a list of all players on an island.";
}
