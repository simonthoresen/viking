#include <std.h>
#include "/d/Empire/empire.h"

inherit I_ARMOUR;

private int _auto_load;

static void
create()
{
    ::create();
    _auto_load = 0;

    set_type("badge");
    set_name("Badge of the Empire");
    set_long("It is a small badge made of rusty scrap metal. It depicts the " +
	     "letter '%^L_BLUE%^E%^RESET%^' within a crude circle. It " +
	     "provides you with access to the commands of the Empire. " +
	     "Try 'help empire'.");
    add_id("badge of the empire");
    add_id(source_file_name());
    add_property("protected", 100);
    add_property("tagged");
    set_weight(0);
    set_value(69);
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public int
drop(int silent)
{
    if (query_verb() != "toss") {
        return NO_DROP;
    }
    return ::drop(silent);
}

public int
wear(int silent)
{
    if (!interactive(environment())) {
        return 0;
    }
    return ::wear(silent);
}

static void
on_move(object from, object to)
{
    if (objectp(from)) {
        from->remove_hook("__damage_dealt");
        from->remove_hook("__heart_beat");
        from->remove_hook("__kill");
	from->remove_cmdpath(EMP_DIR_COM_M);
    }
    if (objectp(to) && living(to)) {
        to->add_hook("__damage_dealt", store_fp("maybe_inflict_critical"));
        to->add_hook("__heart_beat", store_fp("poke_empire_room"));
        to->add_hook("__kill", store_fp("register_kill"));
	to->add_cmdpath(EMP_DIR_COM_M);
        if (interactive(to)) {
            wear(1);
        } else {
            set_short(0);
        }
    }
}

static void
on_destroy()
{
    on_move(environment(), 0);
}

public void
poke_empire_room()
{
    object ply, env;
    if (!objectp(ply = previous_object())) {
        return; /* erm */
    }
    if (!objectp(env = environment(ply)) || !env->is_empire()) {
        return; /* not in empire */
    }
    env->living_heart_beat(ply);
}

public void
maybe_inflict_critical(int dmg, string dtype, object foe, string loc)
{
    object ply, env;
    int val;
    if (!objectp(ply = previous_object()) || !objectp(foe)) {
        return; /* erm */
    }
    if (!objectp(env = environment(ply)) || !env->is_empire()) {
        return; /* not in empire */
    }
    EMP_D_CRITICAL->damage_dealt(ply, foe, dmg, loc);
}

public void
register_kill(object victim, object killer)
{
    EMP_D_ANARCHY->player_kill(victim, killer);
    EMP_D_EXP->player_kill(victim, killer);
}

public string
query_auto_load()
{
    return source_file_name() + ":";
}

public void
init_arg(string arg)
{
    _auto_load = 1;
}
