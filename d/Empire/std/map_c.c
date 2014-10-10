#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void create() {
    ::create();
    set_short("The beautiful coast");
    set_day_long(({ "You are walking along the peaceful coast. Shells have " +
                    "washed up on shore, and some have been ground to fine " +
                    "particles by the beating waves of the deep blue water.",
                    "Walking along the coast, the site of red-orange sand " +
                    "against deep blue water is an awesome sight. Your feet " +
                    "sink into the wet sand as you walk.",
                    "The coast is very beautiful. You can see the sun " +
                    "reflecting brilliantly off the water. The coarse " +
                    "red-orange sand meets deep blue water here." })
                 [random(3)]);
    set_night_long("In the darkness, you can barely make out a reflection " +
                   "of the moon on the water. The slow crashing of waves is " +
                   "the only indication that water is nearby.");
    add_trigger("listen", "You hear the gentle crashing of waves against " +
                "the coast.\n");
}
