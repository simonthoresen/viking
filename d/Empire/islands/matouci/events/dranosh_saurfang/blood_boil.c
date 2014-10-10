#include "/d/Empire/empire.h"

inherit I_ITEM;

private object _caster;

static void
create() 
{
    ::create();
    _caster = 0;
    set_name("boiling blood");
    set_short(0);
    set_drop(1);
    add_id(source_file_name());
    
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
    destroy(30);
}

static void
on_move(object from, object to) 
{
    object env;
    if (objectp(from) && living(from)) {
        tell_object(from, "You blood stops boiling.\n");
        if (objectp(env = environment(from))) {
            tell_room(env, from->query_name() + "'s blood stops boiling.\n",
                      ({ from }));
        }
        from->remove_hook("__heart_beat");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "%^B_RED%^%^L_YELLOW%^\n" +
                    "   ___  ____  ______   _____  _______  ___  __   ____  ____  ___ \n" +
                    "  / _ )/ __ \\/  _/ /  /  _/ |/ / ___/ / _ )/ /  / __ \\/ __ \\/ _ \\\n" +
                    " / _  / /_/ // // /___/ //    / (_ / / _  / /__/ /_/ / /_/ / // /\n" +
                    "/____/\\____/___/____/___/_/|_/\\___/ /____/____/\\____/\\____/____/\n" +
                    "%^END%^\n\n" +
                    bold("Your blood starts to boil!\n"));
        if (objectp(env = environment(to))) {
            tell_room(env, to->query_name() + "'s blood starts to boil!\n",
                      ({ to }));
        }
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
    object ply, env;
    if (!objectp(ply = environment()) || !living(ply) || ply->query_dead() || 
        !objectp(env = bottom_room()) || !objectp(_caster) ||
        (interactive(_caster) && !present(_caster, env)))  
    {
        destroy();
        return;
    }
    EMP_D_COMBAT->hit_player(_caster, ply, 25 + random(25), "magic", 
                             0, this_object());
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
