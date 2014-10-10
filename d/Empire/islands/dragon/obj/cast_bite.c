#include "/d/Empire/islands/dragon.h"

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
    return "bite";
}

public void
special_attack(object foe) 
{
    object ply, env;
    if (!objectp(ply = previous_object()) ||
        !objectp(env = environment(ply)))
    {
        return;
    }
    tell_object(foe, "ONYXIA GOBBLES YOU UP!\n");
    tell_room(env, "Onyxia eats " + foe->query_name() + 
              " whole!\n", ({ foe }));
}

public void
damage_done(int dmg, object foe)
{
    object ply;
    if(!objectp(ply = previous_object()) || !objectp(foe)) {
        return;
    }
    MESSAGE_D->weapon_noise(foe, dmg, "bite", ply);
    EMP_D_COMBAT->wound_player(ply, foe, dmg);
    foe->set_busy_next_round(foe->query_name() + " struggles out of " + 
                             "Onyxia's mouth.\n");
}
