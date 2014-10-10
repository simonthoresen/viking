#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

private int     _throw_in;
private object  _last_foe;
private object  _wife;
private string *_entries;

static void
create()
{
    ::create();
    _throw_in = AEGIR_THROW_COUNTDOWN_BEATS;
    _last_foe = 0;
    _wife     = 0;
    _entries  = ({
        RUN_ISLAND->query_room(10, 60),
        RUN_ISLAND->query_room(11, 66),
        RUN_ISLAND->query_room(21, 49),
        RUN_ISLAND->query_room(22, 49),
        RUN_ISLAND->query_room(22, 57),
        RUN_ISLAND->query_room(23, 50)
    });

    set_name("Aegir");
    set_short("the god of the sea");
    set_long("");
    set_level(66);
    add_property("dangerlevel", 100);
    add_property("guardian");
    add_property("unarmed_damage_type", "cold");
    add_hook("__fight_beat", store_fp("on_fight_beat"));
    add_hook("__beat_stopped", store_fp("on_beat_stopped"));
    add_hook("__die", store_fp("on_die"));

    if (clonep(this_object())) {
        schedule_spawn_daughter();
    }
}

private void
maybe_throw(object foe)
{
    if (_last_foe != foe) {
        _last_foe = foe;
        _throw_in = AEGIR_THROW_COUNTDOWN_BEATS;
    } else if (--_throw_in <= 0) {
        _last_foe = 0;
        EMP_D_COMBAT->hit_player(ply, foe, AEGIR_THROW_DAMAGE1, "Impact");
        EMP_D_COMBAT->throw_player(foe, AEGIR_THROW_FORCE);
        EMP_D_COMBAT->hit_player(ply, foe, AEGIR_THROW_DAMAGE2, "Impact");
        EMP_D_COMBAT->stun_player(foe, AEGIR_THROW_STUN, ply);
    }
}

public void
schedule_spawn_daughter()
{
    call_out_unique("spawn_daughter", AEGIR_DAUGHTER_SPAWN_INTERVAL);
}

public void
spawn_daughter()
{
    schedule_spawn_daughter();
    make(RUN_C_AEGIR_DAUGHTER, _entries[random(sizeof(_entries))]);
}

static void
on_beat_stopped()
{
    object env;
    if (!objectp(env = environment()) || objectp(_wife)) {
        return;
    }
    _wife = make(RUN_C_AEGIR_WIFE, env);
}

static void
on_die(object corpse, object killer)
{
    make(EMP_I_TOKEN, corpse)->add_amount(9);
}

static void
on_fight_beat(object foe)
{
    object ply, foe;
    if (!objectp(ply = this_object()) || !objectp(foe)) {
        return;
    }
    maybe_throw(foe);
}
