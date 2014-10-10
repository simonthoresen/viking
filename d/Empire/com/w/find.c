#include "/d/Empire/empire.h"

inherit CMD_MODULE;

static int main(string arg) {
    object *arr;
    if (!stringp(arg) || !strlen(arg = getopts("d", arg))) {
	return notify_fail("Usage: find [-d] <file>");
    }
    if (file_size(arg + ".c") < 0) {
        return notify_fail("File not found.");
    }
    arr = filter_array(objects(), "is_file", this_object(), arg);
    write(sprintf("%O\n", arr));
    if (opts['d']) {
        arr->destroy();
        write("Deleted " + sizeof(arr) + " objects.\n");
    }
    return 1;
}

static int is_file(object obj, string arg) {
    return source_file_name(obj) == arg;
}

public string short_help() {
    return "Returns a list of all instance of a file.";
}
