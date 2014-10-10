#include "/d/Empire/empire.h"

inherit I_OBJECT;

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
    return 5;
}

public void
special_attack(object foe) 
{
    _frenzy = 1;
    previous_object()->command("emote goes into a mad frenzy!");
} 

public int
query_extra_attack() 
{
    return _frenzy ? 3 + random(2) : 1;
}
