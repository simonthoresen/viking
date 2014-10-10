#include "/d/Artifact/artifact.h"

inherit ART_I_WEAPON_OWNER;

private object _last_weapon;
private string _last_type;

static void
create()
{
    ::create();
    _last_weapon = 0;
    _last_type   = 0;

    add_hook("__bremove", store_fp("silence_remove"));
    add_hook("__bwield", store_fp("silence_wield"));
    add_hook("__remove", store_fp("clear_user_on_remove"));
    add_hook("__wield", store_fp("assign_user_on_wield"));
}

public nomask int
attack()
{
    object usr;
    return objectp(usr = query_user()) ? usr->attack() : 0;
}

public nomask object
query_attack()
{
    object usr;
    return objectp(usr = query_user()) ? usr->query_attack() : 0;
}

public nomask object *
query_attackers()
{
    object usr;
    return objectp(usr = query_user()) ? usr->query_attackers() : 0;
}

private void
notify_wield(object usr)
{
    string str;
    object lhs, rhs;
    if (!objectp(query_control())) {
        return;
    }
    lhs = usr->query_weapon(0);
    rhs = usr->query_weapon(1);
    if (lhs == this_object() && lhs == rhs) {
        str = usr->query_name() + " wields you in both hands.";
    } else if (lhs == this_object()) {
        str = usr->query_name() + " wields you in " +
              usr->query_possessive() + " left hand.";
    } else if (this_object() == rhs) {
        str = usr->query_name() + " wields you in " +
              usr->query_possessive() + " right hand.";
    } else {
        str = usr->query_name() + " wields you.";
    }
    message_player(str + "\n");
}

private void
notify_unwield(object usr)
{
    if (!objectp(query_control())) {
        return;
    }
    message_player(usr->query_name() + " unwields you.\n");
}

static nomask void
silence_wield(object obj, string hand)
{
    silence_echo();
}

static nomask void
assign_user_on_wield(object obj, string hand)
{
    object usr;
    if (!objectp(usr = query_user())) {
        return;
    }
    usr->add_hook("__bkill", store_fp("forward_bkill"));
    usr->add_hook("__damage_dealt", store_fp("forward_damage_dealt"));
    usr->add_hook("__fight_beat", store_fp("forward_fight_beat"));
    usr->add_hook("__hit_player", store_fp("share_damage_taken"));
    usr->add_hook("__kill", store_fp("forward_kill"));
    notify_wield(usr);
}

static nomask void
silence_remove()
{
    silence_echo();
}

static nomask void
clear_user_on_remove()
{
    object usr;
    if (!objectp(usr = query_user())) {
        return;
    }
    usr->remove_hook("__bkill");
    usr->remove_hook("__damage_dealt");
    usr->remove_hook("__fight_beat");
    usr->remove_hook("__hit_player");
    usr->remove_hook("__kill");
    notify_unwield(usr);
}

public nomask void
forward_fight_beat(object foe)
{
    object ply;
    if (!objectp(ply = query_player()) ||
        is_suspended())
    {
        return;
    }
    ply->hook("__fight_beat", ({ foe }));
    ply->write_prompt();
}

public nomask int
share_damage_taken(int dmg, string dtype, object foe, string loc, int prot,
                   int res, int vuln, int ac, object wpn)
{
    object ply, usr;
    int ply_level, usr_level;
    int ply_dmg, usr_dmg, all_dmg;
    int ply_max, usr_max;
    if (!objectp(ply = query_player()) ||
        !objectp(usr = query_user()) ||
        !objectp(foe) ||
        is_suspended() ||
        dtype == "Drain")
    {
        return 0;
    }
    ply_level = ply->query_level();
    usr_level = usr->query_level();
    all_dmg = (dmg - prot - res - vuln - ac);
    switch (random(100)) {
    case 0..49: // share 125% of dmg based on level
        all_dmg = (125 * all_dmg) / 100;
        ply_dmg = (all_dmg * ply_level) / (ply_level + usr_level);
        usr_dmg = (all_dmg * usr_level) / (ply_level + usr_level);
        break;
    case 50..69: // ply takes 100% dmg
        ply_dmg = all_dmg;
        usr_dmg = 0;
        break;
    case 70..89: // usr takes 100% dmg
        ply_dmg = 0;
        usr_dmg = all_dmg;
        break;
    case 90..99: // both take 100% dmg
        ply_dmg = all_dmg;
        usr_dmg = all_dmg;
        break;
    }
    ply_max = ply->query_max_hp();
    usr_max = usr->query_max_hp();
    if (ply_dmg > 350 && usr_max > ply_max) {
        // This was probably meant for a body snatcher with high hp. Let
        // us rescale the damage according to the max hp of the artifact.

        // percent_of_usr_max_hp = (100 * all_dmg) / usr_max;
        // corresponding_ply_hp  = (percent_of_usr_max_hp * ply_max) / 100
        //                       = (ply_max * all_dmg) / usr_max
        // dmg_mod  = ply_dmg - corresponding_ply_hp
        //          = ply_dmg - (ply_max * all_dmg) / usr_max
        // ply_dmg -= dmg_mod;
        // usr_dmg += dmg_mod;
        int dmg_mod;
        dmg_mod = ply_dmg - (all_dmg * ply_max) / usr_max;
        ply_dmg -= dmg_mod;
        usr_dmg += dmg_mod;
    }
    if (ply_dmg > 0) {
        ART_D_MESSAGE->block_noise(this_object(), ply_dmg, usr_dmg,
                                   lower_case(dtype), foe,  wpn);
        hit_player(ply_dmg, dtype, foe, loc, wpn);
    }
    return usr_dmg - all_dmg;
}

public nomask void
forward_damage_dealt(int dmg, string type, object foe, string loc, object wpn)
{
    object ply;
    _last_weapon = wpn;
    _last_type = type;
    if (!objectp(ply = query_player()) ||
        _last_weapon != this_object() ||
        is_suspended())
    {
        return;
    }
    ART_D_MESSAGE->weapon_noise(foe, dmg, type, ply);
    ply->hook("__damage_dealt", ({ dmg, type, foe, loc, wpn }));
    silence_echo();
}

public nomask int
forward_bkill(object victim, object killer)
{
    object ply;
    if (!objectp(ply = query_player()) ||
        _last_weapon != this_object() ||
        is_suspended())
    {
        return 0;
    }
    return ply->bhook("__bkill", ({ victim, killer }));
}

public nomask void
forward_kill(object victim, object killer)
{
    object ply;
    if (!objectp(victim) ||
        !objectp(killer) ||
        !objectp(ply = query_player()) ||
        _last_weapon != this_object() ||
        is_suspended())
    {
        return;
    }
    ART_D_MESSAGE->weapon_kill(victim, _last_type, query_name(),
                               victim->query_name(), victim->query_gender(),
                               ply);
    ply->hook("__kill", ({ victim, killer }));
    ply->add_alignment(ADJ_ALIGNMENT(victim->query_alignment()));
    if (wizardp(victim)) {
        return; /* no death message */
    }
    if (victim->query_death_msg() != "none") {
        silence_echo(); /* additional death message */
    }
    silence_echo();
}
