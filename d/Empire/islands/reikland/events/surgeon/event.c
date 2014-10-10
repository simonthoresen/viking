#include "/d/Empire/empire.h"

inherit EMP_I_EVENT;

static void create() {
    ::create();
    set_room_msg("A surgeon comes for your aid.\n");
    set_nearby_msg("You hear someone screaming 'need a hand?' to the #d.\n");
    add_event_object("surgeon");

}
