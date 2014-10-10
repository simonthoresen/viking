#include "/d/Artifact/artifact.h"

inherit EMP_I_DAEMON;

private int
get_message_index(int dmg)
{
    return MESSAGE_D->get_message_index(dmg);
}

private int
get_death_index()
{
    return MESSAGE_D->get_death_index();
}

private string *
query_noise(string dtype)
{
    return MESSAGE_D->query_noise(dtype);
}

private string
my_format_message(string str, object active, string weapon_name,
                  string name, int gender)
{
    return MESSAGE_D->my_format_message(str, active, weapon_name,
                                        name, gender);
}

private string
desc_part(int val, int max)
{
    if (val < 0) {
        val = 0;
    }
    if (val > max) {
        val = max;
    }
    switch((100 * val) / max) {
    case 0:      return "none";
    case 1..9:   return "an insignificant part";
    case 10..19: return "very little";
    case 20..29: return "little";
    case 30..39: return "some";
    case 40..49: return "just under half";
    case 50..59: return "just over half";
    case 60..69: return "much";
    case 70..79: return "very much";
    case 80..89: return "a lot";
    case 90..99: return "most";
    case 100:    return "all";
    }
}

/* messages ply and usr */
public varargs void
block_noise(object ply_wpn, int ply_dmg, int usr_dmg,
            string dtype, object foe, object foe_wpn)
{
    object ply, usr;
    string attack_desc, block_desc, result_desc;
    if (!objectp(ply_wpn) ||
        !objectp(ply = ply_wpn->query_player()) ||
        !objectp(usr = ply_wpn->query_user()))
    {
        return;
    }
    if (objectp(foe)) {
        attack_desc = I_GRAMMAR->genitive(foe->query_name()) + " attack";
        if (objectp(foe_wpn)) {
            attack_desc += " with " + foe->query_possessive() + " " +
                           foe_wpn->query_name();
        }
    } else if (objectp(foe_wpn)) {
        attack_desc = "the " + foe_wpn->query_name();
    } else {
        attack_desc = "the attack, ";
    }
    block_desc = desc_part(ply_dmg, ply_dmg + usr_dmg) + " of " + attack_desc;
    result_desc = usr_dmg > 0 ? ", but the " + dtype + " follows through" : "";

    tell_object(usr, "You block " + block_desc + " with your " +
                ply_wpn->query_shape() + result_desc + ".\n");
    tell_object(ply, usr->query_name() + " uses you to block " +
                block_desc + result_desc + ".\n");
    tell_room(environment(usr), usr->query_name() + " uses " +
              usr->query_possessive() + " " + ply_wpn->query_shape() +
              " to block " + block_desc + result_desc + ".\n",
              ({ usr, ply_wpn->query_bee() }));
}

/* messages only hitter */
public varargs void
weapon_noise(object victim, int dmg, string dtype, object hitter)
{
    int idx;
    string *noise;
    if (!objectp(victim) || !objectp(hitter)) {
        return;
    }
    idx = get_message_index(dmg);
    noise = query_noise(dtype);
    message(dmg > 0 ? "youhit" : "youmiss",
            "You " + noise[idx] + " " + victim->query_name() +
            noise[idx + 1] + ".\n", hitter);
}

public varargs void
weapon_kill(object victim, string dtype, string weapon_name,
            string victim_name, int victim_gender, object hitter)
{
    int idx;
    string *noise;
    if (!objectp(hitter)) {
        return;
    }
    idx = get_death_index();
    noise = query_noise(dtype);
    message("youhit", my_format_message(noise[idx], hitter, weapon_name,
                                        victim_name, victim_gender),
            hitter);
}
