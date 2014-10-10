#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ITEM;

private object _caster;

static void
create() 
{
    ::create();
    _caster = 0;
    set_name("flames");
    set_short(0);
    set_drop(NO_DROP);
    
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
    set_heart_beat(1);
    destroy(10);
}

static void
on_move(object from, object to) 
{
    object env;
    if (objectp(from) && living(from)) {
        tell_object(from, "You stop burning.\n");
        if (objectp(env = environment(from))) {
            tell_room(env, from->query_name() + " stops burning.\n", 
                      ({ from }));
        }
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "%^B_YELLOW%^%^RED%^YOU CATCH FIRE!%^END%^\n"); 
        if (objectp(env = environment(to))) {
            tell_room(env, to->query_name() + "'s catches fire!\n",
                      ({ to }));
        }
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public void
heart_beat() 
{
    object ply, env;
    if (!objectp(ply = environment()) || !living(ply) || ply->query_dead() || 
        !objectp(env = bottom_room()) || !objectp(_caster) ||
        (interactive(_caster) && !present(_caster, env)))  
    {
        destroy();
        return;
    }
    EMP_D_COMBAT->hit_player(_caster, ply, 20 + random(20), 
                             "fire", 0, "spell");
}

public object
query_caster() 
{
    return _caster;
}

public void
set_caster(object val) 
{
    _caster = val;
}
