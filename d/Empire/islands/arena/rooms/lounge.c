#include "/d/Empire/islands/arena.h"

inherit I_ROOM;

void create() {
    ::create();
    set_light(1);
    set_short("In the arena lounge");
    set_long("You are in a lounge overlooking the arena.");
    add_property(({ "indoors", "underground", "no_fight" }));
    add_exit(ARN_R_ARENA, "east");
}

varargs void long(string arg) {
    object ply;
    string *arr;
    ::long(arg);
    if (!stringp(arg) &&
	objectp(ply = this_player()) && !ply->test_dark(1) && 
	arrayp(arr = ARN_ISLAND->query_livings()) &&
        sizeof(arr = arr - ({ 0 })) > 0) 
    {
        write("You see " + make_list(arr->query_name()) + " in the arena.\n");
    }
}

