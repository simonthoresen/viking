#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

static int
do_cast(object ply, object foe) 
{
    object obj, *arr;
    if (!objectp(obj = ply->query_weapon(1))) {
        obj = ply->query_weapon(2);
    }
    if (is_caster(ply)) {
        if (objectp(obj)) {
            ply->command("emote shoots force-bolts from " +
                         ply->query_possessive() + " " + obj->query_name() +
                         " in all directions.");
        } else {
            ply->command("emote calls forth an explosion of force.");
        }
    } else {
        if (objectp(obj)) {
            ply->command("emote swings " + ply->query_possessive() + " " +
                         obj->query_name() + " with incredible force.");
        } else {
            ply->command("emote throws " + ply->query_objective() + "self " + 
                         "at you with incredible force.");
        }
    }
    map_array(ply->query_attackers(), "try_throw", this_object(), ply);
    return 1;
}

static void
try_throw(object foe, object ply) 
{
    if (EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), "impact") > 20) {
        EMP_D_COMBAT->throw_player(foe, 1 + random(2));
    }
}
