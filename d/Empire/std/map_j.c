#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void create() {
    ::create();
    set_short("A humid jungle");
    set_day_long(({ "The jungle is oppressively hot and humid. Vines hang " +
                    "from the tall trees, and small insects scamper about " +
                    "below.",
                    "Drops of water fall from the leaves of trees high " +
                    "above. An eerie mist collects on the jungle floor, " +
                    "and you are unable to see your feet.",
                    "The heat here is stifling. You see a rather large grey " +
                    "and red snake watching you with irridescent yellow " +
                    "eyes from a nearby tree. The sensation of movement is " +
                    "all around, and you know you are far from alone." })
                 [random(3)]);
    set_night_long("You are filled with the sensation that this is not a " +
                   "good place to be at night as you observe irridescent " +
                   "eyes bobbing around in the dark air.");
    add_hook("__enter_inv", store_fp("check_enter"));
}

static void check_enter(object obj, object from) {
    if (!objectp(obj) || !living(obj) || can_fly(obj)) {
        return;
    }
    if(!random(2 + (int)obj->query_con() / 2)) {
        tell_object(obj, "You struggle through some entangled vines.\n");
        obj->set_busy_next_round();
    }
}
