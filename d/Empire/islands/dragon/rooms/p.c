#include "/d/Empire/islands/dragon.h"

inherit DON_I_ROOM;

void create() {
    ::create();
    set_short("Lair of Onyxia");
    set_long("You are in the lair of the dragon queen Onyxia. This enormous " +
             "cave promises nothing but your own death. The ground is " +
             "damp and moist, and the air reeks of the blood of fallen " +
             "champions. The eggs of the dragon offspring are littered " +
             "about, waiting to hatch at the call of the queen.");
    add_item(({ "egg", "eggs" }),
             "There are eggs spread out just about everywhere. Most are the " +
             "size of a human child, but a few of them are even bigger than " +
             "an adult male. You hope they wont hatch any time soon.");
}
