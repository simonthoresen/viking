#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("In Altdorf");
    set_long("You are on a road running through Altdorf.");
}
