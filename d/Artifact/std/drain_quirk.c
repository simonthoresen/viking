#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private int _drain_hp;
private int _drain_sp;

static void 
create()
{
    ::create();
    _drain_hp = 0;
    _drain_sp = 0;
}

public nomask string
query_info()
{
    string *pos, *neg, *arr;
    pos = ({ });
    neg = ({ }); 
    if (_drain_hp > 0) {
        pos += ({ "hit points" });
    } else if (_drain_hp < 0) {
        neg += ({ "hit points" });
    }
    if (_drain_sp > 0) {
        pos += ({ "spell points" });
    } else if (_drain_sp < 0) {
        neg += ({ "spell points" });
    }
    arr = ({ });
    if (sizeof(pos) > 0) {
        arr += ({ "drains " + desc_rank() + make_list(pos) + " from" });
    }
    if (sizeof(neg) > 0) {
        arr += ({ "restores " + desc_rank() + make_list(pos) + " to"});
    }
    return query_name() + " " + make_list(arr) + " the wielder of the " +
           "artifact during combat.";
}

static void
setup_user(object ply)
{
    ::setup_user(ply);
    ply->add_hook("__fight_beat", store_fp("drain_tick"));
}

static void
unset_user(object ply)
{
    ::unset_user(ply);
    ply->remove_hook("__fight_beat");
}

public void
drain_tick(object foe)
{
    object ply;
    ply = previous_object();
    if (random(100) < 10) {
        string str;
        str = query_weapon()->query_shape();
        if (_drain_hp > 0) {
            tell_object(ply, "Your " + str + " eats away at your life.\n");
        } else if (_drain_hp < 0) {
            tell_object(ply, "Your " + str + " mends your wounds.\n");
        }
        if (_drain_sp > 0) {
            tell_object(ply, "Your " + str + " eats away at your mind.\n");
        } else if (_drain_sp < 0) {
            tell_object(ply, "Your " + str + " calms your mind.\n");
        }
    }
    ply->reduce_hit_point(_drain_hp);
    ply->reduce_spell_point(_drain_sp);
}

public nomask void
set_drain_hp(int val)
{
    _drain_hp = val;
}

public nomask int
query_drain_hp()
{
    return _drain_hp;
}

public nomask void
set_drain_sp(int val)
{
    _drain_sp = val;
}

public nomask int
query_drain_sp()
{
    return _drain_sp;
}


 
