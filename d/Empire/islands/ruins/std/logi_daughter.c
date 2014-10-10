#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

static void
create()
{
    ::create();
    set_long("");
    set_level(66);
    add_property("unarmed_damage_type", "fire");
    add_hook("__beat_stopped", store_fp("on_beat_stopped"));
    add_hook("__fight_beat", store_fp("on_fight_beat"));
}

public void
cast_fire_ball()
{
    int len;
    object *arr, foe;
    call_out("cast_fire_ball", LOGI_DAUGHTER_BALL_INTERVAL);

    if (!arrayp(arr = RUN_ISLAND->query_livings()) ||
        !arrayp(arr = filter_array(arr, "is_target")) ||
        !(len = sizeof(arr)) ||
        !objectp(foe = arr[random(len)]))
    {
        return;
    }
    EMP_D_COMBAT->hit_player(this_object(), foe,
                             LOGI_DAUGHTER_THROW_DAMAGE, "fire");
    EMP_D_COMBAT->throw_player(foe, LOGI_DAUGHTER_THROW_FORCE);
}

static int
is_target(object foe)
{
    return objectp(foe) && !foe<-RUN_I_MONSTER;
}

static void
on_beat_stopped()
{
    cast_fire_ball();
}

static void
on_fight_beat(object foe)
{
    remove_call_out("cast_fire_ball");
}
