#include "/d/Empire/empire.h"

inherit I_ITEM;

private object _caster;

static void
create() 
{
    ::create();
    _caster = 0;
    set_name("mark of death");
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
        tell_object(from, "You are no longer marked for death.\n"); 
        if (objectp(env = environment(from))) {
            tell_room(env, from->query_name() + " is no longer marked " +
                      "for death.\n", ({ from }));
        }
        from->remove_hook("__die");
        from->remove_hook("__hit_player");
        from->remove_hook("__short");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "%^B_RED%^%^L_YELLOW%^\n" +
                  "   __  ______   ___  __ __  ____  ____  ___  _______ ________ __\n" +
                  "  /  |/  / _ | / _ \\/ //_/ / __ \\/ __/ / _ \\/ __/ _ /_  __/ // /\n" +
                  " / /|_/ / __ |/ , _/ ,<   / /_/ / _/  / // / _// __ |/ / / _  /\n" +
                  "/_/  /_/_/ |_/_/|_/_/|_|  \\____/_/   /____/___/_/ |_/_/ /_//_/\n" +
                    "%^END%^\n\n" +
                    bold("You become marked for death!\n"));
        if (objectp(env = environment(to))) {
            tell_room(env, to->query_name() + " becomes marked for " +
                      "death.\n", ({ to }));
        }
        to->add_hook("__die", store_fp("on_target_die"));
        to->add_hook("__hit_player", store_fp("on_target_hit_player"));
        to->add_hook("__short", store_fp("on_target_short"));
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public int
on_target_hit_player(int dmg, string type, object hitter, string loc, 
                     int prot, int resist, int vuln, int ac, object weapon) 
{
    return dmg;
}

public string 
on_target_short() 
{
    return " %^B_RED%^%^L_YELLOW%^[[ Mark of Death ]]%^END%^";
}

public void
on_target_die(object corpse, object killer) 
{
    object victim, env;
    if (!objectp(_caster) || 
        !objectp(env = environment(_caster)) ||
        !objectp(victim = previous_object())) 
    {
        return;
    }
    tell_room(env, bold("The death of " + victim->query_name() + 
                        " heals " + _caster->query_name() + ".\n"), 
              ({ victim, _caster }));
    tell_object(_caster, bold("The death of " + victim->query_name() + 
                              " heals you!\n"));
    tell_object(victim, bold("Your death heals " + _caster->query_name() + 
                             "!\n"));
    _caster->heal_self(16661);
    destroy();
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
