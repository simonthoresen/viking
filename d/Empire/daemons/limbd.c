#include "/d/Empire/empire.h"

inherit I_DAEMON;

private mapping _limbs;

private mapping
create_limbs(string hand)
{
    mapping dat;
    dat = ([ ]);
    dat[hand + " big toe"] = ({ });
    dat[hand + " index toe"] = ({ });
    dat[hand + " middle toe"] = ({ });
    dat[hand + " fourth toe"] = ({ });
    dat[hand + " little toe"] = ({ });
    dat[hand + " foot"] = ({
        hand + " big toe",
        hand + " index toe",
        hand + " middle toe",
        hand + " fourth toe",
        hand + " little toe",
    });
    dat[hand + " leg"] = ({ hand + " foot" });
    dat[hand + " calf"] = ({ hand + " leg" });
    dat[hand + " thigh"] = ({ hand + " calf" });

    dat[hand + " thumb"] = ({ });
    dat[hand + " index finger"] = ({ });
    dat[hand + " middle finger"] = ({ });
    dat[hand + " ring finger"] = ({ });
    dat[hand + " little finger"] = ({ });
    dat[hand + " hand"] = ({
        hand + " thumb",
        hand + " index finger",
        hand + " middle finger",
        hand + " ring finger",
        hand + " little finger",
    });
    dat[hand + " forearm"] = ({ hand + " hand" });
    dat[hand + " arm"] = ({ hand + " forearm" });
    dat[hand + " eye"] = ({ });
    dat[hand + " ear"] = ({ });
    return dat;
}

static void
create()
{
    ::create();
    _limbs = ([ ]);
    _limbs += create_limbs("left");
    _limbs += create_limbs("right");
    _limbs["nose"] = ({ });
    _limbs["head"] = ({ "left eye", "right eye",
                        "left ear", "right ear", "nose" });
}

public int
has_limb(string limb, object ply)
{
    string *arr;
    object obj;
    if (!objectp(ply)) {
        return 0;
    }
    if (!objectp(obj = present(EMP_C_LIMBLOSS, ply)) ||
        !arrayp(arr = obj->query_limbs()))
    {
        return 1;
    }
    return member_array(limb, arr) < 0;
}

private mapping
query_limbs_map(object ply)
{
    mapping dat;
    if (!mapp(dat = ply->query_property(EMP_P_LIMBS))) {
        return _limbs;
    }
    return dat;
}

public string *
query_limbs(object ply)
{
    return filter_array(keys(query_limbs_map(ply)), "has_limb",
                        this_object(), ply);
}

public string *
query_child_limbs(string limb, object ply)
{
    string *ret, *arr;
    int i, len;
    if (!objectp(ply) || !stringp(limb) || !has_limb(limb, ply)) {
        return ({ });
    }
    ret = ({ limb });
    if (!arrayp(arr = query_limbs_map(ply)[limb])) {
        return ret;
    }
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        ret += query_child_limbs(arr[i], ply);
    }
    return ret;
}

public varargs string
query_random_limb(object ply, int fatal)
{
    string *arr;
    int len;
    if (!arrayp(arr = query_limbs(ply))) {
        return 0;
    }
    if (!fatal) {
        arr -= ({ "head" });
    }
    if ((len = sizeof(arr)) == 0) {
        return 0;
    }
    return arr[random(len)];
}

public int
can_cut(object ply, string limb)
{
    object env;
    if (!objectp(ply) || !has_limb(limb, ply)) {
        return 0;
    }
    if (ply->query_property("no_disarm")) {
        string *arr;
        arr = query_child_limbs(limb, ply);
        if (member_array("left hand", arr) >= 0||
            member_array("right hand", arr) >= 0)
        {
            return 0;
        }
    }
    if (ply->query_property("no_headchop") && limb == "head") {
        return 0;
    }
    return 1;
}

public varargs int
cut_limb(object victim, string limb, object killer)
{
    object obj, env;
    if (!objectp(victim) || !has_limb(limb, victim) ||
        !objectp(env = environment(victim)))
    {
        return 0;
    }
    if (victim->query_property("no_special") ||
        env->query_property("no_special"))
    {
        return 0;
    }
    if (!has_limb(limb, victim)) {
        return 0;
    }
    if (!objectp(obj = present(EMP_C_LIMBLOSS, victim))) {
        obj = new(EMP_C_LIMBLOSS);
        obj->move(victim);
    }
    obj->add_limbs(query_child_limbs(limb, victim));

    tell_object(victim, "You loose your " + limb + "!\n");
    tell_room(env, victim->query_name() + " looses " +
              victim->query_possessive() + " " + limb + ".\n",
              ({ victim }));

    if (objectp(obj = EMP_C_LIMB->new_instance(victim, limb, killer))) {
        obj->move(env);
    }
    return 1;
}

public int
can_see(object ply)
{
    if (has_limb("left eye", ply)) {
        return 1;
    }
    if (has_limb("right eye", ply)) {
        return 1;
    }
    return 0;
}

public int
can_wear(object ply, string type)
{
    if (type == "helmet" || type == "amulet") {
        return has_limb("head", ply);
    }
    if (type == "shield") {
        return has_limb("left hand", ply);
    }
    if (type == "ring") {
        string *arr;
        int i, len;
        if (!arrayp(arr = query_limbs(ply))) {
            return 0;
        }
        for (i = 0, len = sizeof(arr); i < len; ++i) {
            if (sscanf(arr[i], "%*s finger")) {
                return 1;
            }
        }
        return 0;
    }
    if (type == "glove") {
        return has_limb("left hand", ply) || has_limb("right hand", ply);
    }
    if (type == "boot") {
        return has_limb("left foot", ply) || has_limb("right foot", ply);
    }
    return 1;
}

public int
can_wield(object ply, string hand)
{
    if (hand == "both hands") {
        if (!has_limb("left hand", ply)) {
            return 0;
        }
        if (!has_limb("right hand", ply)) {
            return 0;
        }
    } else if (!has_limb(hand, ply)) {
        return 0;
    }
    return 1;
}

public int
can_move(object ply)
{
    if (has_limb("left foot", ply)) {
        return 1;
    }
    if (has_limb("right foot", ply)) {
        return 1;
    }
    return 0;
}
