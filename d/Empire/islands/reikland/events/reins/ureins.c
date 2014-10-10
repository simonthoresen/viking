#include "/d/Empire/islands/reikland.h"

inherit RED_DIR_EVENTS + "reins/reins";

static void
create() 
{
    ::create();
    set_name("Horseman's reins");
    set_short("a set of gold-threaded reins");
}

static int
can_mount(object ply, object mob) 
{
    if (!interactive(ply)) {
        return 1;
    }
    if (mob->query_level() > ply->query_level() ||
        mob->query_level() > 19 ||
        mob->query_max_hp() > 1500 ||
        mob->query_wc() > 30) 
    {
        return 0;
    }
    return 1;
}

public int
mount(object mob) 
{
    if (!::mount(mob)) {
        return 0;
    }
    mob->add_hook("__fight_beat", store_fp("maybe_throw_rider"));
    return 1;
}

public void
unmount() 
{
    object mob;
    if (objectp(mob = query_mount())) {
        mob->remove_hook("__fight_beat");
    }
    ::unmount();
}

static void
maybe_throw_rider(object foe) 
{
    object ply, mob;
    int diff;
    if (!objectp(ply = query_rider()) || 
        !objectp(mob = query_mount()) ||
        !interactive(ply))
    {
        return;
    }
    diff = (int)foe->query_level() - (int)mob->query_level();
    if (5 + random(10) > diff) {
        return;
    }
    tell_object(ply, "%^BOLD%^" + mob->query_name() + " throws you off " + 
                mob->query_possessive() + " back.%^END%^\n");
    tell_room(environment(ply), mob->query_name() + " throws " + 
              ply->query_name() + " off " + mob->query_possessive() + 
              " back.\n", ({ ply }));
    ply->set_busy_next_round();
    unmount();
    mob->do_attack(ply);
}
