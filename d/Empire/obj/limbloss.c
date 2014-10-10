#include "/d/Empire/empire.h"

inherit EMP_I_ITEM;

private string *_limbs;
private int     _can_move;
private int     _can_see;

static void
create()
{
    ::create();
    _limbs    = ({ });
    _can_move = 1;
    _can_see  = 1;

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
    return capitalize(environment()->query_pronoun() +
		      " is missing " + add_article(make_list(_limbs)));
}

private void
update()
{
    object ply, obj1, obj2, *arr;
    int i, len;
    if (!objectp(ply = environment())) {
        return;
    }
    if (EMP_D_LIMB->can_see(ply)) {
        if (!_can_see) {
            tell_object(ply, "You can see again.\n");
        }
        _can_see = 1;
    } else {
        if (_can_see) {
            tell_object(ply, "You can not see.\n");
        }
        _can_see = 0;
    }
    if (EMP_D_LIMB->can_move(ply)) {
        if (!_can_move) {
            tell_object(ply, "You can move again.\n");
        }
        _can_move = 1;
    } else {
        if (_can_move) {
            tell_object(ply, "You can not move.\n");
        }
        _can_move = 0;
    }
    if (objectp(obj1 = ply->query_weapon(1)) &&
        !EMP_D_LIMB->can_wield(ply, "right hand"))
    {
        obj1->unwield();
    }
    if (objectp(obj2 = ply->query_weapon(2)) &&
        !EMP_D_LIMB->can_wield(ply, "left hand"))
    {
        obj2->unwield();
    }
    if (objectp(obj1) && obj1 == obj2 &&
        !EMP_D_LIMB->can_wield(ply, "both hands"))
    {
        obj2->unwield();
    }
    for (i = 0, len = sizeof(arr = ply->query_worn_armour()); i < len; ++i) {
        if (EMP_D_LIMB->can_wear(ply, arr[i]->query_type())) {
            continue;
        }
        arr[i]->remove(0, 1);
    }
}

static void
on_move(object from, object to)
{
    if (objectp(from) && living(from)) {
        from->remove_hook("__btest_dark");
        from->remove_hook("__bwield");
        from->remove_hook("__bwear");
        from->remove_hook("__bmove_player");
        from->remove_hook("__heart_beat");
        tell_object(from, "You are whole again!\n");
    }
    if (objectp(to) && living(to)) {
        to->add_hook("__btest_dark", store_fp("maybe_prevent_sight"));
        to->add_hook("__bwield", store_fp("maybe_prevent_wield"));
        to->add_hook("__bwear", store_fp("maybe_prevent_wear"));
        to->add_hook("__bmove_player", store_fp("maybe_prevent_move"));
        to->add_hook("__heart_beat", store_fp("living_heart_beat"));
        update();
    }
}

static void
on_destroy()
{
    on_move(environment(), 0);
}

public void
living_heart_beat()
{
    object ply, env;
    string limb;
    int len;
    if (!objectp(ply = environment()) || !living(ply) || ply->query_dead() ||
        !objectp(env = environment(ply)) ||
        (len = sizeof(_limbs)) == 0)
    {
        destroy();
        return;
    }
    if (ply->query_property(EMP_P_NOREGEN) ||
        ply->query_hp() != ply->query_max_hp())
    {
        return;
    }
    limb = _limbs[0];
    tell_object(ply, "Your " + limb + " grows back!\n");
    tell_room(env, ply->query_name() + "'s " + limb +
              " grows back.\n", ({ ply }));
    _limbs = _limbs[1..len - 1];
    update();
}

public int
maybe_prevent_sight(int silent, int light, int skill, object prev)
{
    object ply;
    if (!objectp(ply = previous_object())) {
        return 0;
    }
    if (_can_see) {
        return 0;
    }
    if (!silent) {
        tell_object(ply, "You have no eyes to see with!\n");
    }
    return 1;
}

public int
maybe_prevent_wield(object obj, string hand)
{
    object ply;
    if (!objectp(ply = previous_object())) {
        return 0;
    }
    if (EMP_D_LIMB->can_wield(ply = previous_object(), hand)) {
        return 0;
    }
    tell_object(ply, "You have no " + hand + "!\n");
    return 1;
}

public int
maybe_prevent_wear(int silent, object obj)
{
    object ply;
    string type;
    if (!objectp(ply = previous_object()) ||
        !objectp(obj) || !stringp(type = obj->query_type()))
    {
        return 0;
    }
    if (EMP_D_LIMB->can_wear(ply, type)) {
        return 0;
    }
    tell_object(ply, "You have nowhere to wear it!\n");
    return 1;
}

public int
maybe_prevent_move(string dir, object from, mixed to)
{
    object ply;
    if (!objectp(ply = previous_object())) {
        return 0;
    }
    if (_can_move) {
        return 0;
    }
    tell_object(ply, "You have no feet to move!\n");
    return 1;
}

public void
set_limbs(string *val)
{
    _limbs = val;
    update();
}

public void
add_limb(string val)
{
    _limbs = ({ val }) + _limbs;
    update();
}

public void
add_limbs(string *val)
{
    _limbs = val + _limbs;
    update();
}

public string *
query_limbs()
{
    return _limbs;
}
