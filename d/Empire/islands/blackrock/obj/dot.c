#include "/d/Empire/islands/blackrock.h"

inherit EMP_I_ITEM;

private object _hitter;
private int    _damage;
private string _dtype;

static void
create() 
{
    ::create();
    _hitter = 0;
    _damage = 0;
    _dtype  = 0;

    set_name("curse");
    set_short(0);
    set_drop(NO_DROP);
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && living(from)) {
        tell_object(from, "You are no longer cursed.\n");
        from->remove_hook("__heart_beat");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "YOU ARE CURSED!\n");
        to->add_hook("__heart_beat", store_fp("on_target_heart_beat"));
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public void
on_target_heart_beat()
{
    int val;
    object ply;
    ply = previous_object();
    if (!objectp(_hitter) || 
        !stringp(_dtype) ||
        _damage <= 0)
    {
        destroy();
        return;
    }
    val = 15 + random(15);
    if (wizardp(ply)) {
        tell_object(ply, "Your wizardhood protects you from the curse.\n");
    } else {
        EMP_D_COMBAT->hit_player(_hitter, ply, val, _dtype, 0, "curse");
    }
    _damage -= val;
}

public void
set_hitter(object val) 
{
    _hitter = val;
}

public object
query_hitter() 
{
    return _hitter;
}

public void
set_damage(int val) 
{
    _damage = val;
}

public int
query_damage(int val) 
{
    return _damage;
}

public void
set_dtype(string val) 
{
    _dtype = val;
}

public string
query_dtype() 
{ 
    return _dtype;
}

