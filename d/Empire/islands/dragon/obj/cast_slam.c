#include "/d/Empire/empire.h"

inherit EMP_I_OBJECT;

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
    return 60 + random(60);
}

public string
query_damage_type() 
{
    return "impact";
}

public void
special_attack(object foe) 
{
    tell_object(foe, bold("\n\nONYXIA SLAMS HER HEAD INTO YOU!\n"));
    tell_room(environment(foe), "Onyxia slams her head into " + 
              foe->query_name() + "!\n", ({ foe }));
}

public void
damage_done(int dmg, object foe) 
{
    object ply;
    if (!objectp(ply = previous_object())) {
        return;
    }
    MESSAGE_D->weapon_noise(foe, dmg, "impact", ply);
    if (dmg > 25) {
        EMP_D_COMBAT->throw_player(foe, dmg / 20, ply->query_last_dir());
    }
}
