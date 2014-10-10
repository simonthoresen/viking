#include "/d/Empire/empire.h"

inherit EMP_C_LIQUID;

private object _hitter;

static void
create() 
{
    ::create();
    _hitter = 0;

    set_name("liquid fire");
    set_color("%^L_YELLOW%^");
    set_long("It is a sticky liquid which is on fire.");
    add_id("fire");
    add_hook("__move", store_fp("on_move"));
    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public object
clone() 
{
    object obj;
    if (!objectp(obj = ::clone())) {
        return 0;
    }
    obj->set_hitter(_hitter);
    return obj;
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && living(from)) {
        tell_object(from, "You are no longer on fire!\n");
        from->remove_hook("__btest_dark");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "\n%^B_YELLOW%^%^RED%^YOU CATCH FIRE!!%^END%^\n\n");
        to->add_hook("__btest_dark", store_fp("prevent_sight"));
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

static void
on_heart_beat() 
{
    object ply;
    int val;
    if (!objectp(ply = environment()) || !living(ply) ||
        !objectp(_hitter)) 
    {
        return;
    }
    val = query_amount();
    if (interactive(_hitter)) {
        if (!objectp(present(_hitter, bottom_room()))) {
            return; /* no remote hit */
        }
        if (val > 50) {
            val = 50;
        }
    }
    EMP_D_COMBAT->hit_player(_hitter, ply, val / 2 + random(val / 2), "fire");
}

public int
prevent_sight(int flag, int light, int night_vision, object prev) 
{
    if (query_amount() < 50) {
        return 0;
    }
    tell_object(previous_object(), "\n%^B_YELLOW%^%^RED%^" +
                "FLAMES FLAMES FLAMES FLAMES FLAMES FLAMES FLAMES FLAMES " +
                "FLAMES!%^END%^\n\n");
    return 1;
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

