#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

static int
do_cast(object ply, object foe) 
{
    string type;
    object obj;
    if (!objectp(obj = ply->query_weapon(1))) {
        obj = ply->query_weapon(2);
    }
    if (is_caster(ply)) {
        type = random_element(ply);
        if (objectp(obj)) {
            ply->command("emote shoots " + add_article(type) + "-ball from " +
                         ply->query_possessive() + " " + obj->query_name() +
                         ".");
        } else {
            ply->command("emote casts " + add_article(type) + "-ball.");
        }
    } else {
        type = random_physical(ply);
        if (objectp(obj)) {
            ply->command("emote makes " + add_article(desc_dtype(type)) + 
                         " attack with " + ply->query_possessive() + " " + 
                         obj->query_name() + ", tearing through armour.");
        } else {
            ply->command("emote makes " + add_article(desc_dtype(type)) + 
                         " attack, tearing through armour.");
        }
    }
    EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), capitalize(type));
    return 1;
}
