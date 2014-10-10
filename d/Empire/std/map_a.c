#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    set_short("The high seas");
    set_day_long("You are in the middle of a beautiful and serene body of " +
                 "water. The water stretches out in all directions.");
    set_night_long("The dark loneliness you experience on the quiet water " +
                   "is profound. Your only companion is the moon hovering " +
                   "on the night sky.");
    add_property(({ "sea", "no_wander" }));
    add_hook("__enter_inv", store_fp("check_enter"));
}

static void
check_enter(object obj, object from)
{
    if (!objectp(obj) || can_fly(obj)) {
        return;
    }
    if (living(obj)) {
        if (!objectp(from) || !from->query_property("water")) {
            tell_object(obj, bold("You splash in deep water!\n"));
        }
        if(!can_swim(obj)) {
            tell_object(obj, "The swim makes you exhausted.\n");
            obj->set_busy_next_round();
        }
    } else if (!can_float(obj)) {
        tell_room(this_object(),
                  capitalize(maybe_add_article(obj->query_short())) +
                  " sinks down in the water.\n");
        obj->destroy();
    } else {
        tell_room(this_object(),
                  capitalize(maybe_add_article(obj->query_short())) +
                  " floats in the water.\n");
    }
}

public void
living_heart_beat(object ply)
{
    if (!objectp(ply) || !living(ply) || can_fly(ply)) {
        return;
    }
    if (can_swim(ply)) {
        if (random(100) < 20) {
            tell_object(ply, "You swim in the deep water.\n");
            tell_room(this_object(), ply->query_name() + " swims in the " +
                      "deep water.\n", ({ ply }));
        }
        return;
    }
    if (random(2)) {
        message("hityou", "You are drowning!\n", ply);
        message("visual", ply->query_name()+" is drowning!\n",
                this_object(), ply);
    } else {
        message("hityou", "You gulp in buckets of water!\n", ply);
        message("visual", ply->query_name() + " gulps in buckets of " +
                "water!\n", this_object(), ply);
    }
    catch(ply->hit_player(40 - random(ply->query_dex()), "Drain",
                          this_object()));
    if (objectp(ply)) {
        ply->remove_attackers(this_object());
    }
}
