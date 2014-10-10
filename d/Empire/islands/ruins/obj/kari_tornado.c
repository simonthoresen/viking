#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

static void
create()
{
    ::create();
    set_name("Tornado");
    set_short("a VIOLENT tornado");
    set_long("It is a mobile, destructive vortex of violently rotating " +
             "winds having the appearance of a funnel-shaped cloud and " +
             "advancing beneath a large storm system.");
    set_level(29);
    set_wandering_chance(100);
    set_wandering_time(1);
    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__hit_player", store_fp("on_hit_player"));
    if (clonep(this_object())) {
        destroy(KARI_TORNADO_DURATION_SECS);
    }
}

static void
on_heart_beat()
{
    map_array(all_inventory(environment()), "apply_aoe_damage");
}

static void
apply_aoe_damage(object foe)
{
    int val;
    if (!objectp(foe) || foe<-RUN_I_MONSTER) {
        return;
    }
    val = EMP_D_COMBAT->hit_player(this_object(), foe,
                                   KARI_TORNADO_DAMAGE, "pierce");
    EMP_D_COMBAT->wound_player(this_object(), foe, val);
}

static void
on_hit_player(int dmg, string type, object foe, string loc,
              int prot, int res, int vuln, int ac, object wpn)
{
    tell_room(environment(), query_name() + " does not seem to be affected " +
              "by the " + WEAR_D->prot_message(lower_case(type)) + ".\n");
    return -dmg;
}
