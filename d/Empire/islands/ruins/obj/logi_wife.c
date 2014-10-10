/* do constant aoe damage */
#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

static void
create()
{
    ::create();
    set_name("Glod");
    set_short("faithfull wife of the god of fire");
    set_long("");
    set_level(66);
    add_property("guardian");
    add_property("unarmed_damage_type", "fire");
    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__hit_player", store_fp("on_hit_player"));
}

static void
on_heart_beat()
{
    if (!objectp(RUN_D_RUINS->query_npc(RUN_C_LOGI))) {
        destroy_later();
        return;
    }
    map_array(all_inventory(environment()), "apply_aoe_damage");
}

static void
apply_aoe_damage(object foe)
{
    if (!objectp(foe) || foe<-RUN_I_MONSTER) {
        return;
    }
    EMP_D_COMBAT->hit_player(this_object(), foe, LOGI_WIFE_AOE_DAMAGE, "fire");
}

static void
on_hit_player(int dmg, string type, object foe, string loc,
              int prot, int res, int vuln, int ac, object wpn)
{
    tell_room(environment(), query_name() + " does not seem to be affected " +
              "by the " + WEAR_D->prot_message(lower_case(type)) + ".\n");
    return -dmg;
}
