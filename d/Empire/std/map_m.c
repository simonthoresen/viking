#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void create() {
    ::create();
    set_short("Tall, stately mountains");
    set_day_long(({ "Climbing these mountains is no small task. Sprouts of " +
                    "grass peek out through cracks in the rock. You can see " +
                    "that the peaks of some nearby mountains are covered " +
                    "with snow.",
                    "You stand at the base of a tall, imposing mountain. " +
                    "You can see others in the distance against a dark " +
                    "purple sky.",
                    "Walking through a mountain pass, you marvel at the " +
                    "beauty and size of the rock formations which tower " +
                    "above you." })[random(3)]);
    set_night_long("The mountains are an eerie and beautiful sight at night. "+
                   "They tower into the starry sky, filling you with awe.");
    add_item(({ "grass", "fresh grass" }),
             "A little grass scattered here and there.");
    add_hook("__enter_inv", store_fp("check_enter"));
}

static void check_enter(object obj, object from) {
    if (!objectp(obj) || !living(obj) || can_fly(obj)) {
        return;
    }
    if(!random(2 + (int)obj->query_con() / 4)) {
        tell_object(obj, "The climb makes you exhausted.\n");
        obj->set_busy_next_round();
    }
}
