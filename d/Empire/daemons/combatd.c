#include <daemons.h>
#include "/d/Empire/empire.h"

#define STUN_DELAY 10

inherit I_DAEMON;

public varargs int
hit_player(object hitter, object victim, int dmg,
           string dtype, string location, mixed weapon)
{
    string name;
    int gender;
    if (!objectp(hitter) || !living(hitter) ||
        !objectp(victim) || !living(victim) || victim->query_dead())
    {
        return 0;
    }
    if (weapon == 0) {
        weapon   = location;
        location = 0;
    }
    name = victim->query_name();
    gender = victim->query_gender();
    dmg = victim->hit_player(dmg, dtype, hitter, location,
                             objectp(weapon) ? weapon : 0);
    dtype = lower_case(dtype);
    if (!objectp(victim) || victim->query_dead()) {
        if (objectp(weapon)) {
            weapon = weapon->query_name();
        }
        if (!stringp(weapon)) {
            weapon = "hit";
        }
        MESSAGE_D->weapon_kill(victim, dtype, weapon, name, gender, hitter);
    } else {
        MESSAGE_D->weapon_noise(victim, dmg, dtype, hitter);
    }
    return dmg;
}

public varargs int
hit_players(object hitter, object *victims, int dmg,
	    string dtype, string location, mixed weapon)
{
    int i, len, ret;
    if (!objectp(hitter) || !living(hitter) ||
	!arrayp(victims))
    {
	return 0;
    }
    ret = 0;
    dmg = dmg / 4;
    for (i = 0, len = sizeof(victims); i < len; ++i) {
	ret += hit_player(hitter, victims[i], dmg * 3 + random(dmg * 2),
                          dtype, location, weapon);
    }
    return ret;
}

private string
query_random_dir(object env)
{
    string *arr;
    int len;
    if (!objectp(env) ||
        !arrayp(arr = env->query_visible_exits()) ||
        (len = sizeof(arr)) == 0)
    {
        return 0;
    }
    return arr[random(len)];
}

public varargs int
throw_player(object ply, int force, string dir)
{
    object env;
    int i;
    if (!objectp(ply) || !living(ply) ||
        !objectp(env = environment(ply)))
    {
        return 0;
    }
    if (ply->query_property("guardian") ||
        env->query_property("no_special"))
    {
        return 0;
    }
    if (force < 1) {
        return 0;
    }
    if (!stringp(dir) &&
        !stringp(dir = query_random_dir(env)))
    {
        return 0;
    }
    for (i = 0; i < force; ++i) {
        string file;
        if (!objectp(ply) || /* could have been destroyed by move */
            !objectp(env = environment(ply)) ||
            !stringp(file = env->query_exit(dir)) ||
            !objectp(env = file->__bootstrap()) ||
            env->query_property("no_wander"))
        {
            break;
        }
        tell_object(ply, "You are thrown " + dir + "ward.\n");
        ply->move_player("flies " + dir, env);
    }
    return i;
}

public varargs int
throw_players(object *ply, int force, string dir)
{
    int i, len, ret;
    if (!arrayp(ply)) {
	return 0;
    }
    ret = 0;
    for (i = 0, len = sizeof(ply); i < len; ++i) {
	ret += throw_player(ply[i], force, dir);
    }
    return ret;
}

private int
can_stun(object victim)
{
}

private int
try_stun(object victim, object hitter)
{
    if (victim->query_tmp_prop("last_stun_hityou") > time() - STUN_DELAY) {
        return 0; // prevent chain stun
    }
    if (objectp(hitter) && victim->hit_player(5, "drain", hitter) <= 0) {
        return 0; // allow resist
    }
    return 1;
}

public varargs int
stun_player(object victim, int dur, object hitter, int force)
{
    object env, obj;
    if (!objectp(victim) || !living(victim) ||
        !objectp(env = environment(victim)))
    {
        return 0;
    }
    if (victim->query_property(EMP_P_NOSTUN) ||
        victim->query_property("no_special") ||
        env->query_property("no_special"))
    {
        return 0;
    }
    if (!force && !try_stun(victim, hitter)) {
        if (objectp(victim)) {
            tell_object(victim, "You resist the stun!\n");
            tell_room(env, victim->query_name() + " resists the stun!\n",
                      ({ victim }));
        }
	return 0;
    }
    if (!objectp(victim) || dur < 1) {
        return 0;
    }
    if (!objectp(obj = present(EMP_C_STUN, victim))) {
        tell_object(victim, bold("You are stunned for " + dur + " rounds!\n"));
        tell_room(env, victim->query_name() + " is stunned.\n", ({ victim }));
        obj = new(EMP_C_STUN);
        obj->move(victim);
        if (!objectp(obj)) {
            return 0; /* destroyed by move */
        }
    } else {
        tell_object(victim, bold("You are stunned for an additional " +
                                 dur + " rounds!\n"));
    }
    obj->add_duration(dur);
    victim->set_tmp_prop("last_stun_hityou",
                         time() + obj->query_duration() * 2);
    return 1;
}

public varargs int
stun_players(object *victims, int dur, object hitter)
{
    int i, len, ret;
    if (!arrayp(victims)) {
	return 0;
    }
    ret = 0;
    for (i = 0, len = sizeof(victims); i < len; ++i) {
	ret += stun_player(victims[i], dur, hitter);
    }
    return ret;
}

public int
wound_player(object hitter, object victim, int dmg)
{
    object env, obj;
    if (!objectp(hitter) || !living(hitter) ||
        !objectp(victim) || !living(victim) ||
        !objectp(env = environment(victim)))
    {
        return 0;
    }
    if (victim->query_property(EMP_P_NOBLOOD) ||
        victim->query_property("undead") ||
        victim->query_property("no_special") ||
        env->query_property("no_special"))
    {
        return 0;
    }
    if (dmg < 1) {
        return 0;
    }
    if (!objectp(obj = present(EMP_C_WOUND, victim))) {
        tell_object(victim, "You start to bleed!\n");
        tell_room(env, victim->query_name() + " starts to bleed.\n",
                  ({ victim }));
        obj = new(EMP_C_WOUND);
        obj->move(victim);
        if (!objectp(obj)) {
            return 0; /* destroyed by move */
        }
    } else {
        tell_object(victim, "You start to bleed even more!\n");
    }
    obj->add_damage(dmg);
    obj->add_hitter(hitter);
    return 1;
}

public varargs int
wound_players(object hitter, object *victims, int dmg)
{
    int i, len, ret;
    if (!objectp(hitter) || !living(hitter) ||
	!arrayp(victims))
    {
	return 0;
    }
    ret = 0;
    dmg = dmg / 4;
    for (i = 0, len = sizeof(victims); i < len; ++i) {
	ret += wound_player(hitter, victims[i], dmg * 3 + random(dmg * 2));
    }
    return ret;
}

public varargs void
apply_liquid(object who, object liquid, int clone_liquid)
{
    object env;
    int val;
    if (!objectp(who) || !living(who) || who->query_invis() ||
        !objectp(liquid))
    {
        return;
    }
    val = liquid->query_amount();
    if (clone_liquid) {
        liquid = liquid->clone();
    }
    liquid->set_amount(val / 2 + random(val / 2));
    liquid->move(who);
    if (!objectp(liquid)) {
        return; /* destroyed by move */
    }
    tell_object(who, "You are " + liquid->query_desc() + ".\n");
    if (objectp(env = bottom_room(who))) {
	tell_room(env, who->query_name() + " is " +
		  liquid->query_desc() + ".\n", ({ who }));
    }
}

public varargs int
spray_liquid(object env, object liquid, mixed exclude)
{
    object *arr;
    if (!objectp(env) || !env->query_property("room")) {
        return 0;
    }
    if (!arrayp(exclude)) {
        exclude = ({ exclude });
    }
    arr = ({ env }) + all_inventory(env) - exclude;
    map_array(arr, "apply_liquid", this_object(), liquid, 1);
    if (objectp(liquid)) {
        liquid->destroy();
    }
    return 1;
}

public varargs int
spray_blood(object env, int val, mixed exclude)
{
    object blood;
    blood = new(EMP_C_BLOOD);
    blood->set_blood(val);
    return spray_liquid(env, blood, exclude);
}
