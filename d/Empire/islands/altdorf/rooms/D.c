#include "/d/Empire/islands/altdorf.h"

#define TRAVEL_COST 250

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("The Niederhafen Docks");
    set_long("You are in the Niederhafen Docks. There are boats arriving " +
             "and leaving all the time. For a mere " + TRAVEL_COST + " " +
             "gold you can hitch a ride with any of them. There is a sign " +
	     "here.");
    add_item("sign",
	     "These are the establishments of Altdorf:\n" +
	     "- Dalbran Fellhammer's [A]rmour Smithy\n" +
	     "- Reik-Talabec Trading [C]ompany\n" +
	     "- The Niederhafen [D]ocks\n" +
	     "- Association of [F]inanciers and Moneylenders\n" +
	     "- Imperial [G]uard barracks and armoury\n" +
	     "- The People's [H]all\n" +
	     "- Hart's [L]odge\n" +
	     "- H[O]spice Priory of Shallya\n" +
	     "- The Imperial [P]ostal Service\n" +
	     "- Krank's Potions and [R]emedies\n" +
	     "- Great [T]emple and Cathedral of Sigmar\n" +
	     "- Tots Blatter's [W]eapon Smithy\n");
    add_exit("/room/jetty2", "larstown", store_fp("require_payment"));
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
