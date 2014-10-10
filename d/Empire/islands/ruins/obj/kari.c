#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

private int _created_at;

static void
create()
{
    ::create();
    _created_at = time();

    set_name("Kari");
    set_short("the god and personification of wind");
    set_long("");
    set_level(66);
    set_bored_secs(300);
    set_wandering_chance(100);
    set_wandering_time(1);
    set_wandering_hook(store_fp("follow_crumbs"));
    add_property("unarmed_damage_type", "impact");
    add_hook("__fight_beat", store_fp("on_fight_beat"));
    add_hook("__die", store_fp("on_die"));
    if (clonep(this_object())) {
        schedule_spawn_acolyte();
        schedule_spawn_tornado();
    }
}

static mixed
follow_crumbs()
{
    object env;
    string str, dst;
    if (objectp(env = environment()) &&
        stringp(str = env->query_crumb()) &&
        stringp(dst = env->query_exit(str)) &&
        !dst->query_property("no_wander"))
    {
        return str; /* follow player */
    }
    return "growl men"; /* stay put */
}

private void
schedule_spawn_acolyte()
{
    call_out_unique("spawn_acolyte", KARI_ACOLYTE_SPAWN_INTERVAL);
}

private void
schedule_spawn_tornado()
{
    call_out_unique("spawn_tornado", KARI_TORNADO_SPAWN_INTERVAL);
}

public void
spawn_acolyte()
{
    make(RUN_C_KARI_ACOLYTE, RUN_ISLAND->query_random_entry());
}

public void
spawn_tornado()
{
    make(RUN_C_KARI_TORNADO,
         RUN_ISLAND->query_room(16 + random(6), 20 + random(7)));
}

private int
query_force()
{
    int val;
    val = ((time() - _created_at) * 100) / KARI_FORCE_BUILD_SECS;
    return max(0, min(100, val));
}

private string
desc_force()
{
    switch (query_force()) {
    case 0:
        return "calm";
    case 1..3:
        return "light air";
    case 4..6:
        return "light breeze";
    case 7..10:
        return "gentle breeze";
    case 11..16:
        return "moderate breeze";
    case 17..21:
        return "fresh breeze";
    case 22..27:
        return "strong breeze";
    case 28..33:
        return "moderate gale";
    case 34..40:
        return "fresh gale";
    case 41..47:
        return "strong gale";
    case 48..55:
        return "whole gale";
    case 56..63:
        return "storm";
    case 64..85:
        return "hurricane";
    case 86..100:
        return "major hurricane";
    default:
        error("illegal index; " + query_force());
    }
}

static void
on_fight_beat(object foe)
{
    // TODO: use force to do damage
}

static void
on_die(object corpse, object killer)
{
    make(EMP_I_TOKEN, corpse)->add_amount(9);
}
