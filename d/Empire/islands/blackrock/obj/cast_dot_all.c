#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

private void
cast_curse(object ply, object foe) 
{
    string type;
    object *arr;
    int i, len;
    type = random_element(ply);
    ply->command("emote casts " + add_article(desc_dtype(type)) + 
                 " curse on you.");
    for (i = 0, len = sizeof(arr = ply->query_attackers()); i < len; ++i) {
        object obj;
        obj = new(resolve_path("dot"));
        obj->set_hitter(ply);
        obj->set_damage(50 + random(50));
        obj->set_dtype(type);
        obj->move(arr[i]);
    }
}

private void
tear_wound(object ply, object foe) 
{
    object obj, *arr;
    if (!objectp(obj = ply->query_weapon(1))) {
        obj = ply->query_weapon(2);
    }
    if (objectp(obj)) {
        ply->command("emote cuts a deep wound in you with " +
                     ply->query_possessive() + " " + obj->query_name() + ".");
    } else {
        ply->command("emote tears a deep wound in you.");
    }
    arr = ply->query_attackers();
    EMP_D_COMBAT->hit_players(ply, arr, 10 + random(10), "claw");
    EMP_D_COMBAT->wound_players(ply, arr, 50 + random(50));
}

static int
do_cast(object ply, object foe) 
{
    object obj;
    if (is_caster(ply)) {
        cast_curse(ply, foe);
    } else {
        tear_wound(ply, foe);
    }
    return 1;
}
