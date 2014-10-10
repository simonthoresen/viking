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

public string
query_damage_type() 
{
    return "fire";
}

public void
special_attack(object foe) 
{
    object ply, env, obj;
    if (!objectp(ply = previous_object()) ||
        !objectp(env = environment(ply)))
    {
        return;
    }
    obj = new(resolve_path("elemball"));
    obj->set_hitter(ply);
    obj->set_direction(ply->query_last_dir());
    tell_room(env, bold("\n\nONYXIA BREATHS A HUGE BALL OF " + 
                        upper_case(obj->query_type()) + "!\n\n\n"));
    obj->move(env);
}
