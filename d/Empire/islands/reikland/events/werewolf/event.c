#include "/d/Empire/islands/reikland.h"

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("A shiver runs down your spine as a wolf howls nearby!\n");
    set_nearby_msg("A wolf howls from the #d.\n");
    add_event_object("werewolf");
    add_hook("__bopen", store_fp("check_time"));
}

static int
check_time(object ply, object env) 
{
    return !EMP_D_TIME->is_night();
}
