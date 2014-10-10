#include "/d/Empire/islands/blackrock.h"

inherit base I_OBJECT;
inherit file EMP_I_FILE;

private int     _cost;
private string *_elements;
private string *_physical;

static void
create() 
{
    base::create();
    file::create();
    _cost     = 25;
    _elements = ({ "fire", "cold", "electricity", "drain", "acid", "magic" });
    _physical = ({ "slash", "blunt", "pierce", "chop", "claw", 
                   "bite", "impact" });
}

static int
is_caster(object ply) 
{
    return objectp(ply) && ply->query_property("magic");
}

private string *
query_dtypes(object ply) 
{
    mixed val;
    object obj;
    if (!objectp(ply)) {
        return ({ });
    }
    val = ({ });
    if (objectp(obj = ply->query_weapon(0))) {
        val += obj->query_damage_type();
    }
    if (objectp(obj = ply->query_weapon(1))) {
        val += obj->query_damage_type();
    }
    if (sizeof(val) > 0) {
        return val;
    }
    if (stringp(val = ply->query_property("unarmed_damage_type"))) {
        return ({ val });
    } 
    if (arrayp(val)) {
        return val;
    }    
    return ({ });
}

static string
random_element(object ply) 
{
    string *arr;
    if (sizeof(arr = query_dtypes(ply) & _elements) == 0) {
        arr = _elements;
    }
    return arr[random(sizeof(arr))];
}

static string
random_physical(object ply) 
{
    string *arr;
    if (sizeof(arr = query_dtypes(ply) & _physical) == 0) {
        arr = _physical;
    }
    return arr[random(sizeof(arr))];
}

static string
desc_dtype(string type) 
{
    switch (lower_case(type)) {
    case "slash":       return "SLASHING";
    case "blunt":       return "CRUSHING";
    case "pierce":      return "PIERCING";
    case "chop":        return "CHOPPING";
    case "claw":        return "CLAWING";
    case "bite":        return "BITING";
    case "fire":        return "BURNING";
    case "cold":        return "FREEZING";
    case "electricity": return "SHOCKING";
    case "impact":      return "ANNIHILATING";
    case "drain":       return "DEVOURING";
    case "acid":        return "SCORCHING";
    case "magic":       return "MAGICAL";
    default:            return "WEIRD";
    }
}

/**
 * Method to be implemented by child. The arguments are guaranteed to be 
 * non-null, and the foe is guaranteed to be present in the same room as 
 * the caster. 
 */
static int
do_cast(object ply, object foe) 
{
    return 0; /* implemented by child */
}

public int
main(object ply, object foe) 
{
    object env;
    string type;
    if (!objectp(ply) && !objectp(ply = this_player())) {
	return 0;
    }
    if (!objectp(foe) && !objectp(foe = ply->query_attack())) {
        return 0;
    }
    if (!objectp(env = environment(ply)) || env != environment(foe)) {
        return 0;
    }
    if (ply->query_sp() < _cost) {
        return 0;
    }
    if (!do_cast(ply, foe)) {
        return 0;
    }
    if (objectp(ply)) {
        ply->reduce_spell_point(_cost);
    }
    return 1;
}

public void
set_cost(int val) 
{
    _cost = val;
}

public int
query_cost() 
{
    return _cost;
}
