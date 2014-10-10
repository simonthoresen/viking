#include "/d/Empire/islands/matouci.h"

#define P_WARNED ("emp_matouci_warned")

inherit I_OBJECT;

object _entry;
object _exit;

object connect_to(string from, string dir, string to) {
    object obj;
    if (!objectp(obj = from->__bootstrap())) {
        return 0;
    }
    obj->add_exit(to, dir, store_fp("show_warning"));
    obj->add_my_desc("A path leads " + dir + " into a dark and " +
                     "foreboding forest. A sign next to the path " +
                     "reads 'DANGER'.");
    obj->add_item(({ "forest", "dark forest", "foreboding forest" }),
                  "It seems very dense. It looks like it would be " +
                  "very easy to get lost there. A chill runs down " +
                  "your spine just by looking at it.");
    obj->add_item(({ "sign" }),
                  "It says 'DANGER'.");
/* 25-Sep-2011: Gaeius adds no wandering */
    call_other(to,"add_property","no_wander");
    return obj;
}

void disconnect_from(object room, string dir) {
    if (!objectp(room)) {
        return;
    }
    room->remove_exit(dir);
    room->remove_my_desc();
}

void create() {
    ::create();
    _entry = connect_to("/room/plane4", "east", 
                        EMP_DIR_VAR_ISLANDS + "matouci/12/1");
    _exit  = connect_to("/room/eastroad2",  "west", 
                        EMP_DIR_VAR_ISLANDS + "matouci/9/76");
}

void on_destruct() {
    ::on_destruct();
    disconnect_from(_entry, "east");
    disconnect_from(_exit, "west");
}

int show_warning() {
    object ply;
    if (!objectp(ply = this_player()) || 
        ply->query_property(P_WARNED)) 
    {
        return 0;
    }
    write("Are you absolutely sure you want to enter the forest? " +
          "It looks really, really dangerous! (yes / no):\n"); 
    input_to("answer_warning", 0, query_verb());
    return 1;
}

void answer_warning(string arg, string dir) {
    object ply, env;
    string dst;
    if (!objectp(ply = this_player()) || 
        !objectp(env = environment(ply)) ||
        !stringp(dst = env->query_exit(dir)))
    {
        return;
    }
    if (!stringp(arg) || arg != "yes") {
        write("Ok.\n");
        return;
    }
    ply->add_property(P_WARNED);
    ply->move_player(dir + "#" + dst);
}

