#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

static void
create()
{
    ::create();
    set_name("Ran");
    set_short("the supportive wife of the god of the sea");
    set_long("");
    set_level(66);
    set_destroy_msg("#N vanishes in a puff of smoke.\n");
    add_property("unarmed_damage_type", "cold");
    add_hook("__damage_done", store_fp("on_damage_done"));
    if (clonep(this_object())) {
        call_out("heal_aegir", 0);
    }
}

public void
heal_aegir()
{
    object npc, env;
    if (!objectp(env = environment()) ||
        !objectp(npc = RUN_D_RUINS->query_npc(RUN_C_AEGIR)) ||
        !objectp(present(npc, env)) ||
        npc->query_hp() > (90 * npc->query_max_hp()) / 100)
    {
        destroy_later();
        return;
    }
    tell_room(env, query_name() + " heals " + npc->query_name() + ".\n");
    npc->reduce_hit_points(-AEGIR_WIFE_TICK_HEAL);
    call_out("heal_aegir", AEGIR_WIFE_TICK_SECS);
}

static void
on_damage_done(int dmg, string type, object hitter, string loc)
{
    destroy_later();
}
