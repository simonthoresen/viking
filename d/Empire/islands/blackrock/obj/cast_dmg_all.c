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
            ply->command("emote shoots " + type + "-bolts from " +
                         ply->query_possessive() + " " + obj->query_name() +
                         " in all directions.");
        } else {
            ply->command("emote summons " + add_article(desc_dtype(type)) +
                         " inferno.");
        }
    } else {
        type = random_physical(ply);
        if (objectp(obj)) {
            ply->command("emote spins around with " + ply->query_possessive() +
                         " " + obj->query_name() + ", hitting everyone.");
        } else {
            ply->command("emote flails all around the room.");
        }
    }
    EMP_D_COMBAT->hit_players(ply, ply->query_attackers(),
                              25 + random(25), type);
    return 1;
}
