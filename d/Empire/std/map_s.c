#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void create() {
    ::create();
    set_short("A murky swamp");
    set_day_long(({ "You find yourself in the middle of a murky swamp. The " +
                    "swamp gas is so thick that at times you swear you are " +
                    "actually swimming in it. You wade through the cloudy " +
                    "water.",
                    "The swamp is interrupted by an occasional outgrowth of " +
                    "trees which can barely be seen through the swamp gas. " +
                    "You wade cautiously so as not to upset the many " +
                    "creatures which lurk beneath the murky waters.",
                    "You push some vines aside as you wade through the " +
                    "swamp. You proceed at a cautious pace since the gas is " +
                    "so thick, you can hardly see your hand in front of " +
                    "your face." })[random(3)]);
    set_night_long("The swamp is not the best place to be at night. The " +
                   "swamp gas floats over the murky waters almost as if it " +
                   "were alive. Your only companion in this dark morass is " +
                   "the sound of the water as it is parted by your stride.");
    add_trigger("smell", "The air is heavy with the stench of decay.\n");
    add_hook("__enter_inv", store_fp("check_enter"));
}

static void check_enter(object obj, object from) {
    if (!objectp(obj) || !living(obj) || can_fly(obj)) {
        return;
    }
    if(!random(2 + (int)obj->query_con() / 4)) {
        tell_object(obj, "You slush through the swamp.\n");
        obj->set_busy_next_round();
    }
}
