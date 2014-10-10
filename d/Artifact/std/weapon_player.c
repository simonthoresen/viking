#include "/d/Artifact/artifact.h"

inherit ART_I_WEAPON_UTIL;

static void
create()
{
    ::create();
    add_hook("__Artifact_player_set", store_fp("setup_player"));
    add_hook("__break", store_fp("kill_player_on_break"));
    add_hook("__destroy", store_fp("clean_player_on_destroy"));
    add_hook("__weapon_hit", store_fp("apply_bonus_on_weapon_hit"));
    add_hook("__wear_out", store_fp("hit_player_on_wear_out"));
}

static nomask void
setup_player(object ply)
{
    ply->add_hook("__add_alignment", store_fp("on_player_add_alignment"));
    ply->add_hook("__bdie", store_fp("on_player_bdie"));
    ply->add_hook("__bkill", store_fp("on_player_bkill"));
    ply->add_hook("__choose_target", store_fp("attack"));
    ply->add_hook("__damage_dealt", store_fp("on_player_damage_dealt"));
    ply->add_hook("__damage_done", store_fp("on_player_damage_done"));
    ply->add_hook("__die", store_fp("on_player_die"));
    ply->add_hook("__drink", store_fp("on_player_drink"));
    ply->add_hook("__eat", store_fp("on_player_eat"));
    ply->add_hook("__hit_player", store_fp("on_player_hit_player"));
    ply->add_hook("__kill", store_fp("on_player_kill"));
    ply->add_hook("__wear", store_fp("on_player_wear"));
    ply->add_hook("__wield", store_fp("on_player_wield"));
}

static nomask void
unset_player(object ply)
{
    ply->remove_hook("__add_alignment");
    ply->remove_hook("__bdie");
    ply->remove_hook("__bkill");
    ply->remove_hook("__choose_target");
    ply->remove_hook("__damage_dealt");
    ply->remove_hook("__damage_done");
    ply->remove_hook("__die");
    ply->remove_hook("__drink");
    ply->remove_hook("__eat");
    ply->remove_hook("__hit_player");
    ply->remove_hook("__kill");
    ply->remove_hook("__wear");
    ply->remove_hook("__wield");
}

public nomask varargs int
hit_player(int dmg, string dtype, object foe, string loc, object wpn)
{
    object ply;
    if (!objectp(ply = query_player()) || is_suspended()) {
        return 0;
    }
    dmg = ply->hit_player(dmg, lower_case(dtype), foe, 0, wpn);
    ply->remove_attackers(foe);
    silence_echo();
    if (ply->query_dead()) {
        MESSAGE_D->weapon_kill(ply, dtype,
                               objectp(wpn) ? wpn->query_name() : "hit",
                               ply->query_name(),
                               ply->query_gender(), foe);
    } else {
        MESSAGE_D->weapon_noise(ply, dmg, dtype, foe);
    }
    return dmg;
}

static nomask mixed
apply_bonus_on_weapon_hit(object foe)
{
    int ret;
    object ply, wpn;
    if (!objectp(ply = query_player()) ||
        ply->query_busy_next_round() ||
        is_suspended() ||
        is_idle())
    {
        return "miss";
    }
    if (query_type() == "twohanded") {
        ret = (ply->query_dex() * 1 + ply->query_str() * 3) / 4;
    } else {
        ret = (ply->query_dex() * 2 + ply->query_str() * 2) / 4;
    }
    if (objectp(wpn = ply->query_weapon(0))) {
        catch(ret += wpn->hit(foe));
    }
    if (objectp(wpn = ply->query_weapon(1))) {
        catch(ret += wpn->hit(foe));
    }
    ret = calc_damage(ply, foe, ret);
    return ret;
}

private object
guess_foe()
{
    object ply, foe;
    if (!objectp(ply = query_owner())) {
        return this_player(); // no owner, use active player
    }
    if (!objectp(foe = ply->query_attack())) {
        return ply;  // owner is not in combat, use owner
    }
    return foe; // owner is in combat, use foe
}

static nomask void
kill_player_on_break(string dtype, int wear)
{
    hit_player(666999, "Drain", guess_foe());
}

static nomask void
clean_player_on_destroy()
{
    object ply;
    if (!objectp(ply = query_player())) {
        return;
    }
    unset_player(ply);
    message_player(bold("\nYOUR PHYSICAL FORM SHATTERS!\n\n"));
    ART_MASTER->clean_member(ply);
}

static nomask int
hit_player_on_wear_out(int wear, string dtype)
{
    object ply;
    int prev, next, full;
    if (!objectp(ply = query_player())) {
        return -wear;
    }
    full = ply->query_max_hp();
    prev = 100 - (100 * ply->query_hp()) / full;

    hit_player((wear * full) / 100, dtype, guess_foe());

    next = 100 - (100 * ply->query_hp()) / full;
    return next - prev - wear;
}

private void
prevent_death()
{
    query_player()->heal_self(666);
    ART_D_SLIVER->make_sliver("second_life_fx", this_object());

    force_drop(1);
    move(ART_R_SMITHY);
}

public nomask int
on_player_bdie(object foe)
{
    object ply;
    ply = previous_object();
    if (random(100) > ply->query_skill("second_life")) {
        return 0;
    }
    if (catch(prevent_death())) {
        // this logic is guarded by a catch() to prevent some random bug from
        // blocking the death guard, but still removing the second_life skill
        return 0;
    }
    ply->remove_skill("second_life");
    tell_object(ply, "\n\n%^BOLD%^YOU ESCAPE DEATH!%^END%^\n\n\n");
    ART_D_QUEST->add_unlock(ply, "second_life_1", 1, 1);
    ART_D_QUEST->add_unlock(ply, "second_life_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "second_life_100", 1, 100);
    return 1;
}

public nomask int
on_player_bkill(object victim, object killer)
{
    // we want to prevent this_player() from scoring the killing blow,
    // since that will grief a wielder that depends on kills
    return killer == query_player() && victim != killer;
}

public nomask void
on_player_add_alignment(int change, int result)
{
    object ply;
    ply = previous_object();
    if (result < 0) {
        ART_D_QUEST->try_unlock(ply, "necromancy_0", -result,
                                -Q_NECROMANCY_ALIGN_LIM);
        ART_D_SCORE->set_score("evilness", ply, -result);
    }
    if (result > 0) {
        ART_D_QUEST->try_unlock(ply, "divination_0", result,
                                Q_DIVINATION_ALIGN_LIM);
        ART_D_SCORE->set_score("holyness", ply, result);
    }
}

public nomask void
on_player_damage_dealt(int dmg, string type, object foe,
                       string loc, object wpn)
{
    int exp, rested;
    object ply;
    if (!objectp(ply = query_player()) ||
        is_suspended() ||
        is_idle())
    {
        return;
    }
    exp = dmg;
    if ((rested = ply->query_property(ART_P_RESTED_EXP)) > 0) {
        exp = (exp * RESTED_EXP_FACTOR) / 100;
        ply->add_property(ART_P_RESTED_EXP, max(0, rested - exp));
    }
    if (objectp(foe) && sizeof(foe->query_attackers()) > 1) {
        if (is_tanking(ply, foe)) {
            exp = (exp * TANK_EXP_FACTOR) / 100;
        } else if (is_assisting(ply, foe)) {
            exp = (exp * ASSIST_EXP_FACTOR) / 100;
        } else {
            // no adjustment
        }
    }
    ply->add_exp(exp);
    ART_D_QUEST->try_unlock(ply, "damage_dealt_30", dmg, 30);
    ART_D_QUEST->try_unlock(ply, "damage_dealt_100", dmg, 100);
    ART_D_SCORE->set_score("hardest hit inflicted", ply, dmg);
}

public nomask void
on_player_damage_done(int dmg, string type, object foe, string loc)
{
    object ply;
    ply = previous_object();
    if (dmg >= Q_SECOND_LIFE_MIN_DAMAGE &&
        ply->query_hp() <= Q_SECOND_LIFE_MAX_HP)
    {
        ART_D_QUEST->unlock(ply, "second_life_0");
    }
    ART_D_SCORE->set_score("hardest hit suffered", ply, dmg);
}

public nomask void
on_player_die(object corpse, object killer)
{
    object ply;
    ply = previous_object();
    ART_D_QUEST->add_unlock(ply, "die_1", 1, 1);
    if (ply->query_level() >= ETERNAL_FIRST) {
        ART_D_QUEST->add_unlock(ply, "die_10", 1, 10);
        ART_D_QUEST->add_unlock(ply, "die_100", 1, 100);
    }
    destroy_later();
}

public nomask void
on_player_drink(object obj)
{
    object ply;
    ply = previous_object();
    ART_D_QUEST->add_unlock(ply, "drink_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "drink_100", 1, 100);
    ART_D_QUEST->add_unlock(ply, "drink_1000", 1, 1000);
}

public nomask void
on_player_eat(object obj)
{
    object ply;
    ply = previous_object();
    ART_D_QUEST->add_unlock(ply, "eat_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "eat_100", 1, 100);
    ART_D_QUEST->add_unlock(ply, "eat_1000", 1, 1000);
}

public nomask void
on_player_hit_player(int dmg, string type, object foe, string loc,
                     int prot, int res, int vuln, int ac, object wpn)
{
    object ply;
    ply = previous_object();
    ART_D_QUEST->add_unlock(ply, "abjuration_0", -prot,
                            Q_ABJURATION_PROT_LIM);
}

public nomask void
on_player_kill(object victim, object killer)
{
    int i, len;
    object ply;
    string *quests, race, creator, arg;
    ply     = previous_object();
    race    = objectp(victim) ? victim->query_race() : "";
    creator = lower_case(creator(victim));
    quests  = ART_D_QUEST->query_items();
    for (i = 0, len = sizeof(quests); i < len; ++i) {
        int lim;
        string quest;
        quest = quests[i];
        if (!starts_with(quest, "kill_")) {
            // cheap test before doing sscanf
            continue;
        }
        if (sscanf(quest, "kill_%s_%d", arg, lim)) {
            if (arg == creator || arg == race || victim->id(arg)) {
                ART_D_QUEST->add_unlock(ply, quest, 1, lim);
            }
            continue;
        }
        if (sscanf(quest, "kill_%d", lim)) {
            ART_D_QUEST->add_unlock(ply, quest, 1, lim);
            continue;
        }
    }
    if (sizeof(({ race }) & Q_CONJURATION_RACES)) {
        ART_D_QUEST->add_unlock(ply, "conjuration_0",
                                1, Q_CONJURATION_KILL_LIM);
    }
}

private void
on_player_equip(object ply, object obj)
{
    ART_D_QUEST->try_unlock(ply, "con_5",  ply->query_tmp_con(), 5);
    ART_D_QUEST->try_unlock(ply, "con_10", ply->query_tmp_con(), 10);
    ART_D_QUEST->try_unlock(ply, "con_11", ply->query_tmp_con(), 11);

    ART_D_QUEST->try_unlock(ply, "dex_5",  ply->query_tmp_dex(), 5);
    ART_D_QUEST->try_unlock(ply, "dex_10", ply->query_tmp_dex(), 10);
    ART_D_QUEST->try_unlock(ply, "dex_11", ply->query_tmp_dex(), 11);

    ART_D_QUEST->try_unlock(ply, "int_5",  ply->query_tmp_int(), 5);
    ART_D_QUEST->try_unlock(ply, "int_10", ply->query_tmp_int(), 10);
    ART_D_QUEST->try_unlock(ply, "int_11", ply->query_tmp_int(), 11);

    ART_D_QUEST->try_unlock(ply, "str_5",  ply->query_tmp_str(), 5);
    ART_D_QUEST->try_unlock(ply, "str_10", ply->query_tmp_str(), 10);
    ART_D_QUEST->try_unlock(ply, "str_11", ply->query_tmp_str(), 11);
}

public nomask void
on_player_wear(int silent, object obj)
{
    mapping dat;
    object ply;
    ply = previous_object();
    ART_D_QUEST->add_unlock(ply, "armour_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "armour_100", 1, 100);
    ART_D_QUEST->add_unlock(ply, "armour_1000", 1, 1000);
    if (mapp(dat = obj->query_wear_modifier())) {
        ART_D_QUEST->add_unlock(ply, "transmutation_0",
                                map_sizeof(dat), Q_TRANSMUTATION_MOD_LIM);
    }
    on_player_equip(ply, obj);
}

public nomask void
on_player_wield(object obj, string hand)
{
    object ply;
    ply = previous_object();
    ART_D_QUEST->add_unlock(ply, "weapon_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "weapon_100", 1, 100);
    ART_D_QUEST->add_unlock(ply, "weapon_1000", 1, 1000);
    on_player_equip(ply, obj);
}
