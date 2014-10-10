#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

static void
create()
{
    ::create();
    set_name("Shade");
    set_short("a shade of the ancient giant");
    set_long("");
    set_level(66);
    set_no_corpse(1);
    add_property("unarmed_damage_type", "magic");
    add_hook("__destroy", store_fp("on_destroy"));
    if (clonep(this_object())) {
        call_out("heal_fornjot", 0);
    }
}

public void
heal_fornjot()
{
    object npc, env;
    if (!objectp(env = environment()) ||
        env->query_island() != RUN_ISLAND ||
        !objectp(npc = RUN_D_RUINS->query_npc(RUN_C_FORNJOT)) ||
        npc->query_hp() > (90 * npc->query_max_hp()) / 100)
    {
        destroy_later();
        return;
    }
    if (objectp(env = environment())) {
        tell_room(env, query_name() + " heals " +
                  npc->query_name() + ".\n");
    }
    if (!present(npc, env) && objectp(env = environment(npc))) {
        tell_room(env, npc->query_name() + " is healed by " +
                  query_name() + ".\n");
    }
    npc->reduce_hit_points(-FORNJOT_SHADE_TICK_HEAL);
    npc->healed_by_shade();
    call_out("heal_fornjot", FORNJOT_SHADE_TICK_SECS);
}

static void
on_destroy()
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, query_name() + " vanishes in a puff of smoke.\n");
}
