#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private string *_dtypes;
private int     _bonus;
private int     _dmg;

static void 
create() 
{
    ::create();
    _dtypes = ({ });
    _bonus  = 0;
    _dmg    = 0;
}

public nomask string 
query_info() 
{
    return "Imbues the weapon with " + make_list(_dtypes) + " damage.";
}

private string *
setup_dtypes(string *orig) 
{
    return orig + _dtypes;
} 

private string *
unset_dtypes(string *orig) 
{
    string *ret;
    int i, len;
    for (i = 0, len = sizeof(_dtypes); i < len; ++i) {
        ret = remove_first(_dtypes[i], orig);
    }
    return ret;
}

static nomask void 
setup_player(object ply) 
{
    int i, len, sum;
    ::setup_player(ply);
    sum = 0;
    for (i = 0, len = sizeof(_dtypes); i < len; ++i) {
        sum += ply->query_skill(_dtypes[i] + "_aptitude");
    }
    _dmg = (_bonus * sum) / (100 * len);
}

static nomask void
setup_weapon(object obj) 
{
    ::setup_weapon(obj);
    obj->set_damage_type(setup_dtypes(obj->query_damage_type()));
    obj->add_hook("__weapon_hit", store_fp("on_weapon_hit"));
}

static nomask void
unset_weapon(object obj) 
{
    ::unset_weapon(obj);
    obj->set_damage_type(unset_dtypes(obj->query_damage_type()));
    obj->remove_hook("__weapon_hit");
}

public nomask int
on_weapon_hit(object foe) 
{
    if (member_array(query_weapon()->query_last_type(), _dtypes) < 0) {
        return 0;
    }
    return _dmg;
}

public nomask string *
query_dtypes() 
{
    return _dtypes;
}

public nomask void 
set_dtypes(string *val) 
{
    _dtypes = val;
}

public nomask void
add_dtype(string val) 
{
    _dtypes += ({ val });
}

public nomask int
query_bonus() 
{
    return _bonus;
}

public nomask void
set_bonus(int val) 
{
    _bonus = val;
}
