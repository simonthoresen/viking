#include "/d/Empire/islands/dragon.h"

inherit DON_I_ROOM;

void create() {
    ::create();
    set_short("Lair of Onyxia");
    set_long("You are in the lair of the dragon queen Onyxia. This enormous " +
             "cave promises nothing but your own death. The ground is " +
             "rougher here than elsewhere in the cave, making movement more " +
             "difficult. There are also the eggs of the dragon offspring " +
             "littered about, waiting to hatch at the call of the queen.");
    add_item(({ "egg", "eggs" }),
             "There are eggs spread out just about everywhere. Most are the " +
             "size of a human child, but a few of them are even bigger than " +
             "an adult male. You hope they wont hatch any time soon.");
    add_hook("__enter_inv", store_fp("check_enter"));
}

static void check_enter(object obj, object from) {
    if (!objectp(obj) || !living(obj) || can_fly(obj) || random(5)) {
        return;
    }
    tell_object(obj, "You trip and fall on some loose rocks.\n");
    tell_room(this_object(), obj->query_name() + 
              " trips and falls on some loose rocks.\n", ({ obj }));
    obj->set_busy_next_round(obj->query_name() + " gets to " +
                             obj->query_possessive() + " feet.\n");
}
