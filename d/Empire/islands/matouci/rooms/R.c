#include "/d/Empire/islands/matouci.h"

inherit EMP_DIR_STD + "map_f";

void create() {
    ::create();
    set_long("You have arrived at a small clearing in the forest. " +
             "There is a wooden cabin here.");
    add_item(({ "clearing" }), 
             "It has just enough room for the cabin.");
    add_item(({ "cabin", "small cabin" }),
             "It look warm and welcoming.");              
    add_exit("/d/Runewaker/master", "enter");
}
