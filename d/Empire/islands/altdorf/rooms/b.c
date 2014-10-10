#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("On a bridge.");
    set_day_long("You are on a bridge crossing the River Reik. As you walk " +
                 "across, you hear it creaking.");
    set_night_long("As you walk across the bridge you see how the moon " +
                   "reflects brilliantly in the water of the River Reik " +
                   "below.");
    add_item(({ "river", "reik" }),
             "The river flows from Nuln in the south, to Altdorf, and on " +
             "to the burgeoning port-city of Marienburg in the Wasteland.");
}
