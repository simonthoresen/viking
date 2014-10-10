#include "/d/Empire/empire.h"

inherit CMD_MODULE;

static int main(string arg) {
    string *arr;
    string name;
    name = this_player()->query_real_name();
    if (!stringp(arg)) {
        arr = EMP_D_LOG->query_files();
        arr = map_array(arr, "mark_watching", this_object(), name);
	write("Logs: " + make_list(arr) + "\n");
	return 1;
    }
    if (EMP_D_LOG->is_watching(arg, name)) {
        write("You stop watching the '" + arg + "' log.\n");
        EMP_D_LOG->remove_watcher(arg, name);
    } else {
        write("You start watching the '" + arg + "' log.\n");
        EMP_D_LOG->add_watcher(arg, name);
    }
    return 1;
}

static string mark_watching(string file, string name) {
    return (EMP_D_LOG->is_watching(file, name) ? "*" : "") + file;
}

public string short_help() {
    return "Toggles the Empire log watch channel.";
}
