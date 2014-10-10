#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

private int _has_daughters;
private int _has_wife;

static void
create()
{
    ::create();
    _has_daughters = 1;
    _has_wife      = 1;

    set_name("Halogi"); // high flame
    set_short("the god and personification of fire");
    set_long("");
    set_level(66);
    add_property("guardian");
    add_property("unarmed_damage_type", "fire");
    add_hook("__beat_stopped", store_fp("on_beat_stopped"));
    add_hook("__fight_beat", store_fp("on_fight_beat"));
    add_hook("__die", store_fp("on_die"));
}

private int
is_below_hp(int percent)
{
    return query_hp() < (percent * query_max_hp()) / 100;
}

private void
maybe_spawn_wife()
{
    if (_has_wife && is_below_hp(LOGI_SPAWN_WIFE_AT)) {
        _has_wife = 0;
        make(RUN_C_LOGI_WIFE, environment());
    }
}

private void
maybe_spawn_daughters()
{
    if (_has_daughters || is_below_hp(LOGI_SPAWN_DAUGHTERS_AT)) {
        _has_daughters = 0;
        make(RUN_C_LOGI_DAUGHTER1, RUN_ISLAND->query_random_entry());
        make(RUN_C_LOGI_DAUGHTER2, RUN_ISLAND->query_random_entry());
    }
}

private void
maybe_throw_player(object foe)
{
    if (random(100) >= LOGI_THROW_CHANCE) {
        return;
    }
    EMP_D_COMBAT->hit_player(this_object(), foe, LOGI_THROW_DAMAGE, "fire");
    EMP_D_COMBAT->throw_player(foe, LOGI_THROW_FORCE);
}

private void
apply_fire(object foe)
{
    object obj;
    if (!objectp(obj = present(RUN_C_LOGI_FIRE, foe))) {
        obj = make(RUN_C_LOGI_FIRE, foe);
    }
    if (objectp(obj)) {
        obj->add_amount(LOGI_FIRE_INC_PER_BEAT);
    }
}

static void
on_fight_beat(object foe)
{
    if (!objectp(foe)) {
        return;
    }
    maybe_spawn_daughters();
    maybe_spawn_wife();
    maybe_throw_player(foe);
    apply_fire(foe);
}

public void
cast_rain_of_fire()
{
    call_out_unique("cast_rain_of_fire", LOGI_RAIN_INTERVAL_SECS);
    command("shout LET THE FIRE RAIN UPON YOU!!");
    map_array(RUN_ISLAND->query_livings(), "apply_rain_of_fire");
}

static void
apply_rain_of_fire(object foe)
{
    if (!objectp(foe) || foe<-RUN_I_MONSTER) {
        return;
    }
    EMP_D_COMBAT->hit_player(this_object(), foe, LOGI_RAIN_DAMAGE, "fire");
}

static void
on_beat_stopped()
{
    cast_rain_of_fire();
}

static void
on_die(object corpse, object killer)
{
    make(EMP_I_TOKEN, corpse)->add_amount(9);
}
