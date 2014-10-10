#include "/d/Empire/islands/ruins.h"

inherit EMP_I_ROOM;

static void
create()
{
    set_short("A gravel road");
    set_day_long(({ "You walk along a gravel road.",
                    "You look around and admire the view as you walk along " +
                    "this gravel road.",
                    "You kick up some gravel as you walk along the road." })
                 [random(3)]);
    set_night_long("The light from the moon and the stars light your way as " +
                   "you walk along this road.");
    add_item(({ "road","gravel road", "gravel" }),
             "The road has been spread with gravel.");
}
