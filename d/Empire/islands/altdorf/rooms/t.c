#include "/d/Empire/islands/altdorf.h"

inherit EMP_DIR_STD + "map_r";

void create() {
    ::create();
    set_short("In the Reikerbahn slums");
    set_day_long("You are on a road through the Reikerbahn slums.");
    set_night_long("You are in a dark alley through the Reikerbahn slums.");
}
