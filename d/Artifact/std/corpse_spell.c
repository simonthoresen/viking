#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private int _heal_hp;
private int _heal_sp;

static void
create()
{
    ::create();
    _heal_hp = 0;
    _heal_sp = 0;
    set_info(query_name() + " heals the artifact by " +
             "sacrificing corpses in the area.");
}

static void
setup_weapon(object wpn)
{
    int cnt;
    object *arr, ply, env;
    ::setup_weapon(wpn);
    env = query_room();
    arr = all_inventory(env);
    arr = filter_array(arr, "is_corpse");
    if ((cnt = sizeof(arr)) == 0) {
        fizzle_spell();
        return;
    }
    tell_room(env, capitalize(I_GRAMMAR->composite_list(arr)) +
              " vanish in a puff of smoke.\n");
    arr->empty(1);
    arr->destroy();

    ply = query_player();
    ply->reduce_hit_point(-_heal_hp * cnt);
    ply->reduce_spell_point(-_heal_sp * cnt);
}

static int
is_corpse(object obj)
{
    return objectp(obj) && obj<-I_CORPSE;
}

public nomask int
query_heal_hp()
{
    return _heal_hp;
}

public nomask void
set_heal_hp(int val)
{
    _heal_hp = val;
}

public nomask int
query_heal_sp()
{
    return _heal_sp;
}

public nomask void
set_heal_sp(int val)
{
    _heal_sp = val;
}
