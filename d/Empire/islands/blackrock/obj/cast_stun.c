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
            ply->command("emote shoots a stun-bolt from " +
                         ply->query_possessive() + " " + obj->query_name() +
                         ".");
        } else {
            ply->command("emote casts a stun-bolt.");
        }
    } else {
        if (objectp(obj)) {
            ply->command("emote makes a stunning attack with " + 
                         ply->query_possessive() + " " + 
                         obj->query_name() + ".");
        } else {
            ply->command("emote makes a stunning attack.");
        }
    }
    EMP_D_COMBAT->hit_player(ply, foe, 10 + random(10), "blunt");
    EMP_D_COMBAT->stun_player(foe, 1 + random(2), ply);
    return 1;
}
