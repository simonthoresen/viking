#include "/d/Empire/empire.h"
#define YELL ("%^L_RED%^DIIIIIIIIE%^L_YELLOW%^!!%^END%^")

inherit EMP_I_EVENT;

static void
create() 
{
    ::create();
    set_room_msg("Someone yells from nearby: " + YELL + "\n");
    set_nearby_msg("Someone yells from the #d: " + YELL + "\n");
    add_event_object("meargh");
}
