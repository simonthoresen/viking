#include "/d/Empire/empire.h"

inherit base I_DAEMON;
inherit util EMP_I_UTIL;

static void
create() 
{
    base::create();
    util::create();
}

public void 
debug(mixed ply, mixed str) 
{
    int i, len;
    mixed *arr;
    if (arrayp(ply)) {
        arr = ply;
    } else {
        arr = ({ ply });
    }
    arr = map_array(arr, "resolve_player") - ({ 0 });
    if (sizeof(arr) == 0) {
        return;
    }
    if (!stringp(str)) {
        str = sprintf("%O", str);
    }
    message("debug", "%^INVERSE%^[DEBUG]: "+ str + "%^END%^\n", arr);
}

static object
resolve_player(mixed ply) 
{
    if (stringp(ply)) {
        ply = find_player(ply);
    }
    if (!objectp(ply)) {
        return 0;
    }
    if (!ply->testbit(PLAYER_DEBUG)) {
        return 0;
    }
    return ply;
}
