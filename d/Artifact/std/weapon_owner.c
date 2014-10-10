#include "/d/Artifact/artifact.h"

inherit ART_I_WEAPON_PLAYER;

static void
create()
{
    ::create();
    add_hook("__get", store_fp("maybe_silence_move"));
    add_hook("__drop", store_fp("maybe_silence_move"));
    add_hook("__move", store_fp("update_owner"));
}

private void
join_party(object owner)
{
    object leader, member;
    if (!objectp(member = query_player())) {
        return;
    }
    if (!objectp(leader = owner->query_party_leader())) {
        owner->add_party_member(owner);
        leader = owner;
    }
    message("party", member->query_name() + " joins the party.\n",
            leader->query_party_members());
    message("party", "You join the party.\n", member);

    leader->add_party_member(member);
    member->set_party_leader(leader);
    member->add_party_member(leader);
    map_array(leader->query_party_members(), "add_party_member", member);
}

private void
leave_party(object owner)
{
    object member, *members;
    if (!objectp(member = query_player())) {
        return;
    }
    members = member->query_party_members();
    member->remove_party_member(member);
    if (arrayp(members)) {
        message("party", member->query_name() + " leaves the party.\n",
                members, member);
    }
    message("party", "You leave the party.\n", member);
}

private void
notify_move(object from, object to)
{
    string str;
    if (!objectp(from) || !objectp(to) || !objectp(query_control())) {
        return;
    }
    if (living(from)) {
        if (living(to)) {
            str = from->query_name() + " gives you to " +
                  to->query_name() + ".";
        } else if (to<-I_ROOM) {
            str = from->query_name() + " drops you on " +
                  "the ground.";
        } else {
            str = from->query_name() + " puts you in " +
                  to->query_name() + ".";
        }
    } else if (from<-I_ROOM) {
        if (living(to)) {
            str = to->query_name() + " picks you up.";
        } else {
            str = 0;
        }
    } else {
        if (living(to)) {
            str = to->query_name() + " takes you out of " +
                  from->query_name() + ".";
        } else {
            str = 0;
        }
    }
    if (stringp(str)) {
        message_player(str + "\n");
    }
}

static nomask void
update_owner(object from, object to)
{
    notify_move(from, to);
    if (objectp(from) && living(from)) {
        from->remove_hook("__blinkdead");
        from->remove_hook("__die");
        from->remove_hook("__invis");
        from->remove_hook("__receive_feeling");
        leave_party(from);
    }
    if (objectp(to) && living(to)) {
        to->add_hook("__blinkdead", store_fp("on_owner_blinkdead"));
        to->add_hook("__die", store_fp("on_owner_die"));
        to->add_hook("__invis", store_fp("on_owner_invis"));
        to->add_hook("__receive_feeling",
                     store_fp("on_owner_receive_feeling"));
        join_party(to);
    }
}

static nomask void
maybe_silence_move(int silent)
{
    if (!silent) {
        silence_echo();
    }
}

public nomask void
on_owner_blinkdead()
{
    force_drop();
}

public nomask void
on_owner_die(object corpse, object killer)
{
    object ply;
    ply = query_player();
    ART_D_QUEST->add_unlock(ply, "owner_die_1", 1, 1);
    if (ply->query_level() >= ETERNAL_FIRST) {
        ART_D_QUEST->add_unlock(ply, "owner_die_10", 1, 10);
        ART_D_QUEST->add_unlock(ply, "owner_die_100", 1, 100);
    }
}

public nomask void
on_owner_invis(int silent)
{
    object ply;
    ply = query_player();
    ART_D_QUEST->add_unlock(ply, "illusionism_0", 1,
                            Q_ILLUSIONISM_INVIS_LIM);
}

public nomask void
on_owner_receive_feeling(string verb, string adv, object act, int type)
{
    object ply;
    ply = query_player();
    if (!objectp(act) || act->query_real_name() == ply->query_real_name()) {
        return;
    }
    if (type & F_AGGRESSIVE) {
        ART_D_QUEST->add_unlock(ply, "aggressive_10", 1, 10);
        ART_D_QUEST->add_unlock(ply, "aggressive_100", 1, 100);
        ART_D_QUEST->add_unlock(ply, "aggressive_1000", 1, 1000);
    }
    if (type & F_FRIENDLY) {
        ART_D_QUEST->add_unlock(ply, "friendly_10", 1, 10);
        ART_D_QUEST->add_unlock(ply, "friendly_100", 1, 100);
        ART_D_QUEST->add_unlock(ply, "friendly_1000", 1, 1000);
        ART_D_QUEST->add_unlock(ply, "enchantment_0", 1,
                                Q_ENCHANTMENT_FRIENDLY_LIM);
    }
    if (type & F_NOISE) {
        ART_D_QUEST->add_unlock(ply, "noise_10", 1, 10);
        ART_D_QUEST->add_unlock(ply, "noise_100", 1, 100);
        ART_D_QUEST->add_unlock(ply, "noise_1000", 1, 1000);
    }
    if (type & F_TOUCHING) {
        ART_D_QUEST->add_unlock(ply, "touching_10", 1, 10);
        ART_D_QUEST->add_unlock(ply, "touching_100", 1, 100);
        ART_D_QUEST->add_unlock(ply, "touching_1000", 1, 1000);
    }
}
