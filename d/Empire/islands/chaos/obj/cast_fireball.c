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
    return 15;
}

public int
query_damage() 
{
    return 25 + random(25);
}

public void
special_attack(object foe) 
{
    tell_room(environment(foe), 
	      "%^B_RED%^%^L_YELLOW%^" + previous_object()->query_name() + 
	      " casts a fireball!%^END%^\n");
}

public int
query_extra_attack() 
{
    return 1;
}

public string
query_damage_type() 
{
    return "fire";
}

public void
damage_done(int dmg, object foe) 
{
    MESSAGE_D->weapon_noise(foe, dmg, "fire", previous_object());
}
