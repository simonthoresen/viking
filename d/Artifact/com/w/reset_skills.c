#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    string *arr;
    object ply;
    int i, len;
    if (!stringp(arg)) {
        ply = this_player();
    } else if (!objectp(ply = find_player(arg))) {
        return notify_fail("No such player.");
    }
    for (i = 0, len = sizeof(arr = keys(ply->query_skill())); i < len; ++i) {
        ply->remove_skill(arr[i]);
    }
    for (i = 0, len = sizeof(arr = ply->query_property()); i < len; ++i) {
        if (sscanf(arr[i], ART_P_SPELL_PREFIX + "%*s")) {
            ply->remove_property(arr[i]);
        }
    }
    write("Ok.\n");
    return 1;
}
