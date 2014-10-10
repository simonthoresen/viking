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
    return 0;
}

public int
query_damage() 
{
    return 25 + random(25);
}

public void
special_attack(object foe) 
{
    previous_object()->command("emote bares its claws.");
}

public string
query_damage_type() 
{
    return "claw";
}

public void
damage_done(int dmg, object foe) 
{
    MESSAGE_D->weapon_noise(foe, dmg, "claw", previous_object());
}
