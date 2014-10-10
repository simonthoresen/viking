#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

static int
do_cast(object ply, object foe) 
{
    string type;
    object obj;
    int val;
    if (!objectp(obj = ply->query_weapon(1))) {
        obj = ply->query_weapon(2);
    }
    if (is_caster(ply)) {
        type = random_element(ply);
        if (objectp(obj)) {
            ply->command("emote shoots " + add_article(type) + "-bolt from " +
                         ply->query_possessive() + " " + obj->query_name() +
                         ".");
        } else {
            ply->command("emote casts " + add_article(type) + "-bolt.");
        }
    } else {
        type = random_physical(ply);
        if (objectp(obj)) {
            ply->command("emote makes " + add_article(desc_dtype(type)) + 
                         " attack with " + ply->query_possessive() + " " + 
                         obj->query_name() + ".");
        } else {
            ply->command("emote makes " + add_article(desc_dtype(type)) + 
                         " attack.");
        }
    }
    val = EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), type);
    if (type == "drain" && val > 0) {
        ply->reduce_hit_point(-val);
    }
    return 1;
}
