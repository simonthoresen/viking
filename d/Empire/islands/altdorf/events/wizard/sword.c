#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_WEAPON;

static void
create()
{
    ::create();

    set_name("Sword of Wisdom");
    set_short("the Sword of Wisdom");
    set_long("This sword is long and solid. The shaft is covered " +
             "with diamonds.");
    add_id(({ "sword", "longsword", "sword of wisdom", "wisdom" }));
    add_property(({ "artifact", "iron", "diamond" }));
    set_class(19);
    set_weight(4);
    set_value(1000 + random(500));
    set_damage_type(({ "slash", "fire", "cold", "electricity",
                       "acid", "magic" }));
    set_hit_func(this_object());
    set_wield_modifier("int", 3, 11);
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
}

public int
query_effect()
{
    object ply;
    int val;
    if (!objectp(ply = query_wield())) {
        return 0;
    }
    if ((val = ply->query_max_sp()) <= 0) {
        return 0;
    }
    val = (10 * ply->query_sp()) / val;
    return val < 0 ? 0 : (val < 10 ? val : 10);
}

static void
on_wield(object weapon, string hand)
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    tell_object(ply, "You feel wise wielding this sword.\n");
    ply->add_hook("__fight_beat", store_fp("on_wielder_fight_beat"));
}

static void
on_remove()
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    tell_object(query_wield(), "You feel stupid again.\n");
    ply->remove_hook("__fight_beat");
}

public void
on_wielder_fight_beat(object foe)
{
    object ply;
    if (!objectp(ply = query_wield()) || !objectp(foe)) {
        return;
    }
    if (random(40) > query_effect()) {
        return; /* 25% chance at full sp */
    }
    tell_object(ply, "The sword shivers and starts to glow.\n");
    ply->do_attack(foe, this_object());
}

public int
query_cost()
{
    return 10 + (10 * query_effect()) / 10;
}

public int
query_damage()
{
    return (25 * query_cost()) / 10;
}

public int
query_extra_attack()
{
    return ({ 0, 0, 0, 0, 1, 1, 1, 2, 2, 3 })[random(query_effect())];
}

public int
weapon_hit(object foe)
{
    int mul;
    mul = interactive(query_wield()) ? 25 : 5;
    return (mul * query_effect()) / 10;
}

public void
damage_done(int dmg, object foe)
{
    MESSAGE_D->weapon_noise(foe, dmg, query_last_type(), query_wield());
}
