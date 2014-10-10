#include "/d/Empire/islands/dragon.h"

inherit EMP_I_OBJECT;

private string _type;

static void
create() 
{
    ::create();
    _type = 0;
}

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
query_damage() {
    return 30 + random(30);
}

public string
query_damage_type()
{
    return _type;
}

public void
special_attack(object foe) 
{
    _type = ({ "fire", "cold", "electricity", "acid", "magic" })[random(5)];
    tell_room(environment(foe), previous_object()->query_name() +
              " casts " + add_article(_type) + "-bolt!\n");
}

public void
damage_done(int dmg, object foe) 
{
    MESSAGE_D->weapon_noise(foe, dmg, _type, previous_object());
}
