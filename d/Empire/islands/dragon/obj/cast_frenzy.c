#include "/d/Empire/islands/dragon.h"

inherit EMP_I_OBJECT;

private int _frenzy;

public void
main(object ply, object foe) 
{
    if (!objectp(ply) || !objectp(foe)) {
	return;
    }
    _frenzy = 0;
    ply->do_attack(foe, this_object());
}

public int
query_cost() 
{
    return 15;
}

public string
query_damage_type() 
{
    return "bite";
}

public void
special_attack(object foe) 
{
    _frenzy = 1;
    tell_room(environment(foe), bold("\nONYXIA GOES INTO A MAD FRENZY!\n"));
}

public int
query_extra_attack() 
{
    return _frenzy ? 3 + random(3) : 1;
}
