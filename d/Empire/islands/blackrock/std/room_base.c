#include "/d/Empire/islands/blackrock.h"

inherit EMP_I_ROOM;

static void create() {
    ::create();
    set_light(-set_light(0));
    set_short("In the depths of Blackrock mountain");
    set_long("You are in a labyrinth of caves in the depths of Blackrock " +
	     "mountain. The caves have been dug recently, and there are " +
	     "wooden supports every few meters to keep the roof from " +
	     "falling down. There is a slight draft of fresh air.");
    add_item(({ "support", "wooden support" }),
	     "The wooden supports are placed every few meters.");
    add_item(({ "roof" }),
	     "The supports keep it from coming down on you.");
    add_item(({ "cave", "caves" }),
	     "You are in them.");
    add_item(({ "blackrock", "mountain" }),
	     "This is the Blackrock mountain, so named for the blackness of " +
	     "its rock.");
    add_item(({ "rock" }),
	     "It is black.");
    add_property(({ "underground", "no_telein" }));
}
