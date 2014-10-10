#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

static int
do_cast(object ply, object foe) 
{
    object obj;
    if (!objectp(obj = ply->query_weapon(1))) {
        obj = ply->query_weapon(2);
    }
    if (is_caster(ply)) {
        if (objectp(obj)) {
            ply->command("emote shoots a force-bolt from " +
                         ply->query_possessive() + " " + obj->query_name() +
                         ".");
        } else {
            ply->command("emote casts a force-bolt.");
        }
    } else {
        if (objectp(obj)) {
            ply->command("emote swings " + ply->query_possessive() + " " +
                         obj->query_name() + " with a lot of force.");
        } else {
            ply->command("emote throws " + ply->query_objective() + "self " + 
                         "forwards.");
        }
    }
    if (EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), "impact") > 20) {
        EMP_D_COMBAT->throw_player(foe, 1 + random(2));
    }
    return 1;
}
