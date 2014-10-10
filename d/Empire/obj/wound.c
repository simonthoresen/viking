#include "/d/Empire/empire.h"

inherit EMP_I_ITEM;

private object *_hitters;
private int     _damage;

static void
create()
{
    ::create();
    _hitters = ({ });
    _damage  = 0;
    set_name(source_file_name());
    set_short(0);
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public int
drop(int silent)
{
    return NO_DROP;
}

public string
extra_look()
{
    return capitalize(environment()->query_pronoun() + " is bleeding");
}

private object
find_hitter(object ply)
{
    object env;
    int i, len;
    if (!objectp(ply) || !objectp(env = environment(ply))) {
        return 0;
    }
    if ((len = sizeof(_hitters -= ({ 0 }))) == 0) {
        return 0;
    }
    if (interactive(ply)) {
        return _hitters[0];
    }
    for (i = 0; i < len; ++i) {
        object foe;
        if (objectp(foe = present(_hitters[i], env))) {
            return _hitters[i];
        }
    }
    return 0;
}

static void
on_move(object from, object to)
{
    if (objectp(from) && living(from)) {
        from->remove_hook("__heart_beat");
        tell_object(from, "You stop bleeding.\n");
    }
    if (objectp(to) && living(to)) {
        to->add_hook("__heart_beat", store_fp("bleed_from_wound"));
    }
}

static void
on_destroy()
{
    on_move(environment(), 0);
}

public void
bleed_from_wound()
{
    object ply, foe, env, obj;
    int dmg;
    if (!objectp(ply = environment()) || !living(ply) || ply->query_dead() ||
        !objectp(foe = find_hitter(ply)) ||
        !objectp(env = environment(ply)) ||
        _damage < 0)
    {
        destroy_later();
        return;
    }
    dmg = min(ply->query_max_hp() / 4, 10 + _damage / 4);
    message("hityou", "You take " + dmg + " damage from your wounds!\n", ply);
    message("combat", ply->query_name()+" takes damage from " +
            ply->query_possessive() + " wounds.\n", env, ply);
    if (!objectp(obj = present(EMP_C_BLOOD, ply))) {
        obj = new(EMP_C_BLOOD);
        obj->set_victim(ply);
        obj->move(ply);
    }
    obj->add_blood(dmg);
    ply->hit_player(dmg, "drain", foe);
    _damage -= dmg;
}

public void
set_hitters(object *val)
{
    _hitters = val;
}

public void
add_hitter(object val)
{
    _hitters += ({ val });
}

public object *
query_hitters()
{
    return _hitters;
}

public void
set_damage(int val)
{
    _damage = val;
}

public void
add_damage(int val)
{
    _damage += val;
}

public int
query_damage()
{
    return _damage;
}
