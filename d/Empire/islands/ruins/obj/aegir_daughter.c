#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

private string
lookup_name(int n)
{
    switch (n) {
    case 0:  return "Bara";
    case 1:  return "Blodughadda";
    case 2:  return "Bylgja";
    case 3:  return "Dufa";
    case 4:  return "Hefring";
    case 5:  return "Himinglaeva";
    case 6:  return "Hronn";
    case 7:  return "Kolga";
    case 8:  return "Unnr";
    default: error("Index out of range; " + n);
    }
}

static void
create()
{
    int n;
    ::create();
    n = random(9);
    set_name(lookup_name(n));
    set_short("the " + I_GRAMMAR->convert_ordinal_number(n + 1) +
              " daughter of Aegir");
    set_long("");
    set_level(66);
    set_no_corpse(1);
    set_wandering_chance(100);
    set_wandering_time(2);
    add_property("unarmed_damage_type", "cold");
    add_hook("__move_player", store_fp("on_move_player"));
    add_hook("__wander_done", store_fp("on_wander_done"));
}

private void
wander_to_aegir(object npc)
{
    object env;
    if (!objectp(env = environment(npc))) {
        return;
    }
    command("shout I AM COMING, FATHER!");
    set_goal(env->query_map_row(), env->query_map_col());
}

private void
merge_with_aegir(object npc, object env)
{
    command("shout I AM HERE, FATHER!");
    npc->restore_hit_poits(-RUN_AEGIR_DAUGHTER_HEAL);
    destroy_later();
}

static void
on_move_player(string dir, object from, mixed to)
{

    int pos;
    object env;
    if (to == 0 ||
        to->query_island() != RUN_ISLAND ||
        !objectp(env = to->__bootstrap()) ||
        !objectp(npc = RUN_D_RUINS->query_npc(RUN_C_AEGIR)))
    {
        destroy_later();
        return;
    }
    if (!objectp(from)) {
        wander_to_aegir(npc);
    }
    map_array(all_inventory(to), "stun_living");
    if (present(npc, env)) {
        merge_with_aegir(npc, env);
    }
}

static void
stun_living(object ply)
{
    if (!objectp(ply) || !living(ply) || ply<-RUN_I_MONSTER) {
        return;
    }
    EMP_D_COMBAT->hit_player(this_object(), ply,
                             AEGIR_DAUGHTER_STUN_DAMAGE, "impact");
    EMP_D_COMBAT->stun_player(ply, AEGIR_DAUGHTER_STUN_DURATION);
}

static void
on_wander_done()
{
    destroy_later();
}
