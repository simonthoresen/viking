#include "/d/Artifact/artifact.h"

public object query_weapon();

static void
create()
{
    // empty
}

public nomask int
is_tanking(object ply, object foe)
{
    object wpn, usr;
    if (!objectp(ply) ||
        !objectp(foe) ||
        !objectp(wpn = query_weapon()) ||
        !objectp(usr = wpn->query_wield()))
    {
        return 0;
    }
    return sizeof(foe->query_attackers()) > 1 && foe->query_attack() == usr;
}

public nomask int
is_assisting(object ply, object foe)
{
    object wpn, usr;
    if (!objectp(ply) ||
        !objectp(foe) ||
        !objectp(wpn = query_weapon()) ||
        !objectp(usr = wpn->query_wield()))
    {
        return 0;
    }
    return sizeof(foe->query_attackers()) > 1 && foe->query_attack() != usr;
}

public varargs nomask int
calc_damage(object ply, object foe, int dmg, string dtype)
{
    if (objectp(ply) && stringp(dtype)) {
        dmg = (dmg + ply->query_skill(dtype + "_aptitude") / 10);
    }
    if (is_tanking(ply, foe)) {
        dmg = (dmg * TANK_DMG_FACTOR) / 100;
    } else if (is_assisting(ply, foe)) {
        dmg = (dmg * ASSIST_DMG_FACTOR) / 100;
    } else {
        /* no modification */
    }
    return dmg;
}
