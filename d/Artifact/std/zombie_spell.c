#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private int     _max_level;
private int     _num_zombies;
private int     _zombie_life;
private int     _zombie_wc;
private object *_zombies;

static void
create()
{
    ::create();
    _max_level   = 0;
    _num_zombies = 0;
    _zombie_life = 0;
    _zombie_wc   = 0;
    _zombies     = ({ });
}

public nomask string
query_info()
{
    return query_name() + " raises " + convert_number(_num_zombies) +
           " dead to fight again for " + format_time(query_duration()) + ".";
}

static void
setup_user(object usr)
{
    int i, len;
    object *arr;
    ::setup_user(usr);
    arr = all_inventory(query_room());
    arr = filter_array(arr, "is_corpse");
    if ((len = sizeof(arr)) == 0) {
        fizzle_spell();
        return;
    }
    arr = sort_array(arr, "cmp_corpse");
    for (i = 0; i < len && i < _num_zombies; ++i) {
        object obj;
        obj = ART_C_ZOMBIE->raise_corpse(arr[i]);
        obj->set_hp(_zombie_life);
        obj->add_property("unarmed_damage_type", ({ "claw", "bite" }));
        obj->add_property("unarmed_weapon_class", _zombie_wc);
        obj->set_master(usr);
        _zombies += ({ obj });
    }
}

static void
unset_user(object usr) 
{
    ::unset_user(usr);
    _zombies -= ({ 0 });
    _zombies->move_player("X", R_VOID);
    _zombies->destroy();
}

static int
is_corpse(object obj)
{
    return objectp(obj) && obj<-I_CORPSE && obj->query_level() <= _max_level;
}

static int
cmp_corpse(object lhs, object rhs)
{
    return rhs->query_level() - lhs->query_level();
}

public nomask int
query_max_level()
{
    return _max_level;
}

public nomask void
set_max_level(int val)
{
    _max_level = val;
}

public nomask int
query_num_zombies()
{
    return _num_zombies;
}

public nomask void
set_num_zombies(int val)
{
    _num_zombies = val;
}

public nomask int
query_zombie_life()
{
    return _zombie_life;
}

public nomask void
set_zombie_life(int val)
{
    _zombie_life = val;
}

public nomask int
query_zombie_wc()
{
    return _zombie_wc;
}

public nomask void
set_zombie_wc(int val)
{
    _zombie_wc = val;
}

public nomask object *
query_zombies()
{
    return _zombies;
}
