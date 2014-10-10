#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

static int
do_cast(object ply, object foe) 
{
    object obj, *arr;
    string type;
    if (!objectp(obj = ply->query_weapon(1))) {
        obj = ply->query_weapon(2);
    }
    if (is_caster(ply)) {
        if (objectp(obj)) {
            ply->command("emote shoots a blinding flash of light from " + 
                         ply->query_possessive() + " " + obj->query_name() +
                         ".");
            type = "magic";
        } else {
            ply->command("emote summons a blinding flash of light.");
            type = "magic";
        }
    } else {
        if (objectp(obj)) {
            ply->command("emote slams " + ply->query_possessive() + " " + 
                         obj->query_name() + " into the ground, making you " +
                         "spasm and jerk horribly.");
            type = "impact";
        } else {
            ply->command("emote lets out a terrifying shreak.");
            type = "drain";
        }
    }
    arr = ply->query_attackers();
    EMP_D_COMBAT->hit_players(ply, arr, 10 + random(10), type);
    EMP_D_COMBAT->stun_players(arr, 1 + random(2), ply);
    return 1;
}
