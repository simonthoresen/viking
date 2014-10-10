#include "/d/Empire/empire.h"

inherit CMD_MODULE;

static int main(string arg) {
    object obj;
    string err;
    if (!stringp(arg)) {
        return notify_fail("Usage: igen <island>");
    }
    obj = make(EMP_C_ISLANDGEN, this_player());
    if (stringp(err = catch(obj->set_island(arg)))) {
        obj->destroy();
        return notify_fail(err);
    }
    if (!obj->execute()) {
        obj->destroy();
        return notify_fail("Task was not accepted.");
    }
    write("Ok.\n");
    return 1;
}

public string short_help() {
    return "Generates the virtual rooms of an island.";
}
