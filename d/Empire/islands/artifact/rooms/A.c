#include "/d/Empire/islands/artifact.h"

inherit EMP_DIR_STD + "map_j";

static void
create()
{
    ::create();
    set_short("Hut of enlightenment");
    set_long("You have arrived at a clearing in the humid jungle. There is " +
             "a small wooden hut here.");
    add_property("no_nothing");
    add_item(({ "hut", "small hut", "wooden hut" }), "You may enter it.");
    add_exit(ART_MASTER, "enter");
}
