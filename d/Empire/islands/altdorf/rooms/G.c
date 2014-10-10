#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("Imperial Guard Barracks and Armoury");
    set_long("You are in the Imperial Guard Barracks and Armoury. This is " +
             "where the city guards come before and after their shifts. " +
	     "There is a map of patrol routes on the wall.");
    add_property("indoors");
    add_reset_object("reidar", ALT_DIR_OBJ + "reidar", 1);
    add_reset_object("guard", ALT_C_SENTRY, 1);

    add_item(({ "map", "routes", "patrol routes" }), store_fp("exa_map"));
}

void exa_map() {
    object *guards, ply;
    string *view;
    int i, len, ansi;
    if (!objectp(ply = this_player()) ||
	!arrayp(view = ALT_ISLAND->query_map())) 
    {
        return;
    }
    if (!arrayp(guards = ALT_ISLAND->find_guards())) {
        guards = ({ });
    }
    view = copy(view);
    for (i = 0, len = sizeof(guards); i < len; ++i) {
        string prev, next;
        object obj, env;
        int row, col;
        if (!objectp(obj = guards[i]) || 
            !objectp(env = environment(obj)))
        {
            continue;
        }
        row = env->query_map_row();
        col = env->query_map_col();
        prev = view[row];
        next = "";
        if (col > 0) {
            next += prev[0..col - 1];
        }
        next += "X";
        if (col < strlen(prev) - 1) {
            next += prev[col + 1..strlen(prev) - 1];
        }
        view[row] = next;
    }
    ply = this_player();
    ansi = (string)ply->query_property("TERM") == "ansi";
    write("It shows you the whereabouts of all Altdorf guard patrols:\n");
    tell_ansi(ply, implode(ALT_ISLAND->format_view(view, ansi), "\n") + "\n");
}
