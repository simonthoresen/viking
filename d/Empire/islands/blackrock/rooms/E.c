#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_ROOM;

static void create() {
    ::create();
    set_light(1);
    set_short("Just inside the Blackrock depths");
    set_long("You are just inside the labyrinth of caves in the depths of " +
	     "the Blackrock mountain. There is a wooden ladder here leading " +
	     "back up to the surface. Further in lies only darkness. There " +
	     "is some light shining through from above.");
    add_item(({ "ladder", "wooden ladder" }),
	     "It leads back up to the surface.");
    add_item(({ "light" }),
	     "It is coming from outside.");
    add_exit(BRD_R_ENTRY, "up");
    add_property("dangerlevel", 0);
}
