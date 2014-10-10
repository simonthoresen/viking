#include "/d/Empire/empire.h"
#define MAX_ATTACKS 8

inherit EMP_I_WEAPON;

private int _anger;

static void
create() 
{
    ::create();
    _anger = 0;

    set_name("sword");
    set_short("a heavy broadsword");
    set_long("The mainstay of the fighter's arsenal, the longsword is " +
             "crafted from choice steel. It's edge is sharp and its point " +
             "allows stabbing attacks.\n");
    add_id(({ "broadsword", "heavy broadsword" }));
    set_class(14 + random(3));
    set_weight(5);
    set_value(1333);
    set_hit_func(this_object());
    set_damage_type(({ "chop", "pierce", "slash", "slash", "slash" }));
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
}

public int 
weapon_hit(object foe) 
{
    return 5;
}

static void
on_wield(object obj, string hands) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->add_hook("__fight_beat", store_fp("maybe_frenzy"));
}

static void
on_remove() 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->remove_hook("__fight_beat");
}

public void
maybe_frenzy(object foe) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    if (_anger < ply->query_str() ||
        ply->query_tmp_prop("last_speed_attack") == time()) 
    {
        if (random(100) < 33) {
            tell_object(ply, "You feel your anger building up.\n");
            _anger += random(ply->query_str());
        }
    } else {
        int i, len;
        tell_object(ply, "Anger overcomes you, and you spin around as a " +
                    "whirling dervish.\n");
        ply->add_tmp_prop("last_speed_attack", time());
        for (i = 0, len = max(1 + random(_anger / 5), MAX_ATTACKS); 
             i < len; ++i) 
        {
            if (!objectp(foe) || foe->query_dead()) {
                break;
            }
            ply->attack();
        }
        _anger = 0;
    }
}

public void
set_anger(int val) 
{
    _anger = val;
}

public int
query_anger() 
{
    return _anger;
}
