#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ARMOUR;

private int _hits;
private int _charges;

static void
create()
{
    ::create();
    _hits    = 0;
    _charges = 0;

    set_name("Ring of Wisdom");
    set_short("the Ring of Wisdom");
    set_long("This ring is made of pure iron, and has a inscription " +
             "saying '" + bold("shock") + "' on it");
    set_type("ring");
    add_id(({ "ring of wisdom", "ring" }));
    add_property("iron");
    set_ac(1);
    set_weight(1);
    set_value(1000 + random(500));
    set_wear_modifier("int", 1, 11);
    add_trigger("shock", store_fp("do_shock"));
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
}

public int
query_effect()
{
    object ply;
    int val;
    if (!objectp(ply = query_worn_by())) {
        return 0;
    }
    if ((val = ply->query_max_sp()) <= 0) {
        return 0;
    }
    val = (10 * ply->query_sp() / val);
    return val < 0 ? 0 : (val < 10 ? val : 10);
}

static void
on_wear(int silent)
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->add_hook("__fight_beat", store_fp("on_wearer_fight_beat"));
}

static void
on_remove()
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__fight_beat");
}

public void
on_wearer_fight_beat(object foe)
{
    object ply;
    if (!objectp(ply = query_worn_by()) || !objectp(foe)) {
        return;
    }
    if (++_hits >= 10 && _charges < 3) {
        tell_object(ply, "The ring glows as it charges up.\n");
        ++_charges;
        _hits = 0;
    }
}

public int
query_cost()
{
    return 50 + random(50);
}

public int
query_damage()
{
    return (18 * query_cost()) / 10;
}

public string
query_damage_type()
{
    return "Electricity";
}

public void
damage_done(int dmg, object foe)
{
    MESSAGE_D->weapon_noise(foe, dmg, "electricity", query_worn_by());
}

public int
do_shock(string arg)
{
    object ply, env, foe;
    int dmg;
    if (!objectp(ply = query_worn_by()) ||
        !objectp(env = environment(ply))) {
        return 0;
    }
    if (stringp(arg)) {
        if (!objectp(foe = present(arg, environment(ply)))) {
            return notify_fail("There is no '" + arg + "' here.");
        }
    } else {
        if (!objectp(foe = ply->query_attack())) {
            return notify_fail("Shock who?");
        }
    }
    if (_charges < 1) {
        return notify_fail("Nothing happens.");
    }
    if (env->query_property("no_mattack")) {
        return notify_fail("This area prevents it.");
    }
    if (!ply->do_attack(foe, this_object())) {
        return notify_fail("You can not attack that.");
    }
    tell_object(ply, "Your ring starts to hum.\n");
    --_charges;
    return 1;
}

public int
query_charges()
{
    return _charges;
}

public void
set_charges(int val)
{
    _charges = val;
}
