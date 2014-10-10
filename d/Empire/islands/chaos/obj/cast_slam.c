#include "/d/Empire/empire.h"

inherit I_OBJECT;

public void
main(object ply, object foe) 
{
    if (!objectp(ply) || !objectp(foe)) {
	return;
    }
    ply->do_attack(foe, this_object());
}

public int
query_cost() 
{
    return 5;
}

public int
query_damage() 
{
    return 25 + random(50);
}

public void
special_attack(object foe) 
{
    tell_room(environment(foe), previous_object()->query_name() + 
	      " throws " + previous_object()->query_objective() + 
	      "self forwards.\n");
} 

public string
query_damage_type() 
{
    return "impact";
}

public void
damage_done(int dmg, object foe) 
{
    MESSAGE_D->weapon_noise(foe, dmg, "impact", previous_object());
    if (dmg > 25) {
	EMP_D_COMBAT->throw_player(foe, dmg / 25);
    }
}
