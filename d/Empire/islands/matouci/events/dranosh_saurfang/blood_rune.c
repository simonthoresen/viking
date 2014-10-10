#include "/d/Empire/empire.h"

inherit I_ITEM;

private object _caster;

static void
create() 
{
    ::create();
    _caster = 0;
    set_name("rune of blood");
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
        tell_object(from, "You are no longer cursed.\n");
        if (objectp(env = environment(from))) {
            tell_room(env, from->query_name() + " is no longer cursed.\n",
                      ({ from }));
        }
        from->remove_hook("__hit_player");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "%^B_RED%^%^L_YELLOW%^\n" +
                    "   ___  __  ___  ______  ____  ____  ___  __   ____  ____  ___\n" +
                    "  / _ \\/ / / / |/ / __/ / __ \\/ __/ / _ )/ /  / __ \\/ __ \\/ _ \\\n" +
                    " / , _/ /_/ /    / _/  / /_/ / _/  / _  / /__/ /_/ / /_/ / // /\n" +
                    "/_/|_|\\____/_/|_/___/  \\____/_/   /____/____/\\____/\\____/____/\n" +              
                    "%^END%^\n\n" +
                    bold("You are cursed!\n"));
        if (objectp(env = environment(to))) {
            tell_room(env, to->query_name() + " is cursed!\n", ({ to }));
        }
        to->add_hook("__hit_player", store_fp("on_target_hit_player"));
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public void
on_target_hit_player(int dmg, string type, object hitter, string loc, 
                     int prot, int resist, int vuln, int ac, object weapon)
{
    object env, victim;
    if (!objectp(_caster) ||
        !objectp(env = environment(_caster)) ||
        !objectp(victim = previous_object()) || 
        _caster != hitter)
    {
        return;
    }
    tell_room(env, "The pain of " + victim->query_name() + 
              " heals " + _caster->query_name() + ".\n", 
              ({ victim, _caster }));
    tell_object(_caster, "The pain of " + victim->query_name() + 
                " heals you!\n");
    tell_object(victim, "Your pain heals " + _caster->query_name() + 
                "!\n");
    _caster->reduce_hit_point(-dmg);
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
