#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

private void
cast_curse(object ply, object foe) 
{
    string type;
    object obj;
    type = random_element(ply);
    tell_object(foe, ply->query_name() + " casts " + 
                add_article(desc_dtype(type)) + " curse on you.\n");
    tell_room(environment(ply), ply->query_name() + " casts " +
              add_article(desc_dtype(type)) + " curse on " +
              foe->query_name() + ".\n", ({ foe }));
    obj = new(resolve_path("dot"));
    obj->set_hitter(ply);
    obj->set_damage(50 + random(50));
    obj->set_dtype(type);
    obj->move(foe);
}

private void
tear_wound(object ply, object foe) 
{
    object obj;
    if (!objectp(obj = ply->query_weapon(1))) {
        obj = ply->query_weapon(2);
    }
    if (objectp(obj)) {
        tell_object(foe, ply->query_name() + " cuts a deep wound in you with " +
                    ply->query_possessive() + " " + obj->query_name() + ".\n");
        tell_room(environment(ply), ply->query_name() + " cuts a deep wound " +
                  "in " + foe->query_name() + " with " +
                  ply->query_possessive() + " " + obj->query_name() + ".\n",
                  ({ foe }));
    } else {
        tell_object(foe, ply->query_name() + " tears a deep wound in you.\n");
        tell_room(environment(ply), ply->query_name() + " tears a deep wound " +
                  "in " + foe->query_name() + ".\n", ({ foe }));
    }
    EMP_D_COMBAT->hit_player(ply, foe, 10 + random(10), "claw");
    EMP_D_COMBAT->wound_player(ply, foe, 50 + random(50));
}

static int
do_cast(object ply, object foe) 
{
    if (is_caster(ply)) {
        cast_curse(ply, foe);
    } else {
        tear_wound(ply, foe);
    }
    return 1;
}
