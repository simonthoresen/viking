#include "/d/Empire/empire.h"

inherit EMP_I_EVENT;

void create() {
    ::create();
    set_cooldown(60 * 60);
    add_event_object("angron");
}
