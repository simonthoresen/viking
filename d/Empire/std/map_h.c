#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void create() {
    ::create();
    set_day_long(({ "The rolling hills are covered by fresh grass. In some " +
                    "places, the grass is bare, indicating poor rainfall. " +
                    "Small prairie creatures scamper about.",
                    "Rocks jut out through the hills here, giving them the " +
                    "appearance of small mountains. The sun is warm here.",
                    "You are walking in between two large hills. The rest " +
                    "of the terrain is obscured by their presence. The " +
                    "hills are covered by dark purple grass and weeds with " +
                    "occasional patches of bare rock." })[random(3)]);
    set_night_long("The faint glint of the moonlight off the rolling hills " +
                   "is an impressive sight. You are filled with a profound " +
                   "sense of loneliness as you look off into the distance.");
    set_short("Rolling hills");
    add_item(({ "grass", "fresh grass" }), 
             "A little grass scattered here and there.");
    add_hook("__enter_inv", store_fp("check_enter"));
}

static void check_enter(object obj, object from) {
    if (!objectp(obj) || !living(obj) || can_fly(obj)) {
        return;
    }
    if(!random(2 + (int)obj->query_con() / 2)) {
        tell_object(obj, "The terrain is exhausting.\n");
        obj->set_busy_next_round();
    }
}
