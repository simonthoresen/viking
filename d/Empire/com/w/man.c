#include "/d/Empire/empire.h"

inherit CMD_MODULE;

static int main(string arg) {
    object *arr;
    if (!stringp(arg)) {
	return 0;
    }
    if (file_size(EMP_DIR_HELP + arg) < 0) {
        return 0;
    }
    this_player()->more(EMP_DIR_HELP + arg);
    return 1;
}

public string short_help() {
    return "Show help files for Empire library.";
}
