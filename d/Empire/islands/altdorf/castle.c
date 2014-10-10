#include "/d/Empire/empire.h"

#define TRAVEL_COST 250

inherit I_OBJECT;

object _entry;

void create() {
    ::create();
    if (objectp(_entry = "/room/jetty2"->__bootstrap())) {
        _entry->add_exit(EMP_DIR_VAR_ISLANDS + "altdorf/16/40", "altdorf", 
                         store_fp("require_payment"));
        _entry->add_my_desc("For a mere " + TRAVEL_COST + " gold you can " +
                            "hitch a ride with one of the boats to Altdorf.");
    }
}

void on_destruct() {
    ::on_destruct();
    if (objectp(_entry)) {
        _entry->remove_exit("altdorf");
        _entry->remove_my_desc();
    }
}

int require_payment() {
    object ply;
    if (!objectp(ply = this_player()) || ply->query_dead()) {
        return 0;
    }
    if (ply->query_money() < TRAVEL_COST) {
        write("You do not have enough money.\n");
        return 1;
    }
    write("You pay " + TRAVEL_COST + " gold to one of the captains.\n");
    say(ply->query_name() + " pays one of the captains some money.\n");
    ply->add_money(-TRAVEL_COST);
    return 0;
}
