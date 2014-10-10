#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    set_short("A pool of lava");
    set_day_long(({ "In a burning pool of red-hot lava.",
                    "On the edge in a pool of burning red-hot lava.",
                    "In the middle of a burning pool of red-hot lava " +
                    "stretching widely in all directions." })[random(3)]);
    set_night_long(query_day_long());
    set_light(1);
    add_property(({ "afire", "no_wander" }));
    add_hook("__enter_inv", store_fp("check_enter"));
}

static void
check_enter(object obj, object from)
{
    if (!objectp(obj) || can_fly(obj)) {
        return;
    }
    if (living(obj)) {
        if (!objectp(from) || !from->query_property("afire")) {
            tell_object(obj, bold("You sink into hot lava!!!\n"));
        }
        call_out("check_burn", 0, obj);
    } else if (random(100) > obj->query_property("prot_fire")) {
        tell_room(this_object(),
                  capitalize(maybe_add_article(obj->query_short())) +
                  " is consumed by the lava.\n");
        obj->destroy();
    }
}

static void
check_burn(object ply)
{
    if (!objectp(ply) || !living(ply) || can_fly(ply)) {
        return;
    }
    message("hityou", "You are burning up!\n", ply);
    message("visual", ply->query_name()+" is burning up!\n",
            this_object(), ply);
    catch(ply->hit_player(5, "Fire", this_object()));
    if (objectp(ply)) {
        catch(ply->hit_player(25 + random(25), "fire", this_object()));
    }
    if (objectp(ply)) {
        ply->remove_attackers(this_object());
    }
}

public void
living_heart_beat(object ply)
{
    check_burn(ply);
}
