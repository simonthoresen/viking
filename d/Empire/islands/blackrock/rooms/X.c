#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_ROOM;

static void create() {
    object obj;
    ::create();
    set_light(1);
    set_short("At the heart of Blackrock mountain");
    set_long("You have reached the innermost sanctuary of the labyrinth of " +
	     "Blackrock mountain, a vertical tunnel that extends from its " +
	     "peak down to the core of the earth. In the center of the dead " +
	     "drop, out of the black depth, rises a pillar of rock. Bridges " +
	     "span from every entrance to a platform on the pillar, on which " +
	     "sits a black rock throne.");
    add_item(({ "sanctuary" }),
	     "This is the innermost room of Blackrock mountain.");
    add_item(({ "blackrock", "mountain" }),
	     "You are at its center.");
    add_item(({ "labyrinth" }),
	     "You have found its sanctuary.");
    add_item(({ "bridge", "narrow bridge" }),
	     "It extends across the vertical drop to the platform.");
    add_item(({ "shaft", "vertical shaft" }),
	     "Looking up you see the sky far above. " +
	     "Looking down you see nothing.");
    add_item(({ "platform" }),
	     "The platform is set on the black rock pillar.");
    add_item(({ "throne", "rock throne" }),
	     "It is made of black rock, and it looks intimidating.");
    add_exit(R_VOID, "down", store_fp("prevent_down"));
    add_exit(R_VOID, "up", store_fp("prevent_up"));
    remove_property("underground");
    add_property("dangerlevel", 100);
    add_reset_object("treasure", BRD_DIR_OBJ + "treasure", 1);
}

static int prevent_down(string arg) {
    write("It is too far down, you would fall to your death.\n");
    return 1;
}

static int prevent_up(string arg) {
    write("The walls are too slippery, you fail.\n");
    return 1;
}
