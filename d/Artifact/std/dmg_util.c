#include "/d/Artifact/artifact.h"

inherit ART_I_DAMAGE_BASE;

private int    _dmg;
private string _dtype;

static void 
create() 
{
    ::create();
    _dmg   = 0;
    _dtype = 0;
}

private void
apply_bite(object ply, object usr, object foe, int dmg)
{
    if (dmg > 10) {
        EMP_D_COMBAT->wound_player(usr, foe, dmg / 2);
    }
    if (dmg > 25) {
        foe->set_busy_next_round(foe->query_name() + " struggles out of " + 
                                 ply->query_name() + "'s mouth.\n");
    }
}

private void
apply_claw(object ply, object usr, object foe, int dmg)
{
    if (dmg > 10) {
        EMP_D_COMBAT->wound_player(usr, foe, dmg / 2);
    }
}

private void
apply_impact(object ply, object usr, object foe, int dmg)
{
    if (dmg > 25 && random(100) < 25) {
        EMP_D_COMBAT->stun_player(foe, 1, usr);
    }
    if (dmg > 50 && random(100) < 5) {
        EMP_D_COMBAT->throw_player(foe, 1);
    }
}

static nomask int
apply_damage(object ply, object usr, object foe)
{
    int dmg;
    dmg = calc_damage(ply, foe, _dmg, _dtype);
    dmg = dmg / 2 + random(dmg / 2);
    dmg = EMP_D_COMBAT->hit_player(usr, foe, dmg, _dtype, ply->query_name());
    if (dmg <= 0 || !objectp(foe) || foe->query_dead()) {
        return dmg;
    }
    switch (lower_case(_dtype)) {
    case "bite":
        apply_bite(ply, usr, foe, dmg);
        break;
    case "claw":
        apply_claw(ply, usr, foe, dmg);
        break;
    case "impact":
        apply_impact(ply, usr, foe, dmg);
        break;
    }
    return dmg;
}

public nomask void 
set_damage(int val) 
{
    _dmg = val;
}

public nomask int
query_damage()
{
    return _dmg;
}

public nomask void 
set_dtype(string val) 
{
    _dtype = val;
}

public nomask string
query_dtype()
{
    return _dtype;
}

