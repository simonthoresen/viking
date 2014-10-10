#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void create() {
    ::create();
    set_short("A dark and eerie forest");
    set_day_long(({ "The sun is mostly obscured by the stately trees of " +
                    "this forest. Small animals regard you cautiously as " +
                    "you walk through the dense foliage.",
                    "Small animals hang about from the trees and squeak at " +
                    "you as you pass by. A bed of dead leaves lies about on " +
                    "the forest floor, and it crunches softly as you walk " +
                    "about.",
                    "You have reached a small clearing in the forest " +
                    "surrounded by tall trees and dense foliage. The grass " +
                    "is VERY tall here, and you have trouble walking " +
                    "through it." })[random(3)]);
    set_night_long("The forest is truly an intimidating place at night. " +
                   "Sounds echo out from near and far, filling you with " +
                   "the sensation of being watched. You step gingerly, " +
                   "careful not to upset the many deadly creatures known " +
                   "to lurk about at night.");
    add_trigger("smell", "The smell of evergreens pervades your nostrils.\n");
    add_neg(({ "smell" }),({ "evergreen", "evergreens" }),
            "The evergreens smell very pleasant.\n");
    add_item(({ "tree", "trees" }),
             "The trees are tall and beautiful.");
    add_item(({ "grass", "fresh grass", "forestbed" }),
             "A little grass in the forestbed.");
    add_hook("__enter_inv", store_fp("check_enter"));
}

static void check_enter(object obj, object from) {
    if (!objectp(obj) || !living(obj) || can_fly(obj)) {
        return;
    }
    if(!random(2 + (int)obj->query_con())) {
        tell_object(obj, "You walk among the trees.\n");
        obj->set_busy_next_round();
    }
}
