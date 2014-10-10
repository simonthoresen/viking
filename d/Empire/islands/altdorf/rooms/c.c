#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("At the river bank");
    set_long("You are standing on the bank of the great River Reik.");
    add_item(({ "river", "reik" }),
             "The river flows from Nuln in the south, to Altdorf, and on " +
             "to the burgeoning port-city of Marienburg in the Wasteland.");
    add_item(({ "water" }),
             "It stretches across to the other side of the river.");
}
