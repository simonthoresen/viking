#include "/d/Empire/empire.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("A woman approaches while singing a beautiful song.\n");
    set_nearby_msg("You hear someone singing to the #d.\n");
    add_event_object("huldra");
    add_hook("__bopen", store_fp("check_time"));
}

static int
check_time(object ply, object env) 
{
    return !EMP_D_TIME->is_night();
}
