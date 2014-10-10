#include <std.h>
#include "/d/Empire/empire.h"

#define UNBLOCKED_VERBS (({ "l", "look", "i", "inventory", "score" }))

inherit I_ITEM;

private int _duration;

static void
create()
{
    ::create();
    _duration = 0;
    set_name(source_file_name());
    set_short(0);
    add_property("protected", 100);
    add_property("no_nothing");
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public int
drop(int silent)
{
    return NO_DROP;
}

public string
extra_look()
{
    return capitalize(environment()->query_pronoun() + " is stunned");
}

public void
init()
{
    object ply;
    ::init();
    if (!objectp(ply = this_player()) || ply != environment()) {
        return;
    }
    ply->set_busy_next_round();
    add_action("do_stun", "", 1);
}

public int
do_stun(string arg)
{
    object ply;
    if (!objectp(ply = this_player()) || ply->query_ghost()) {
        return 0;
    }
    if (member_array(query_verb(), UNBLOCKED_VERBS) > -1) {
        return 0;
    }
    write("You are stunned!\n");
    return !ply->query_property(EMP_P_NOSTUN);
}

static void
on_move(object from, object to)
{
    if (objectp(from) && living(from)) {
        from->remove_hook("__heart_beat");
        tell_object(from, "YOU CAN MOVE AGAIN!!\n");
    }
    if (objectp(to) && living(to)) {
        to->add_hook("__heart_beat", store_fp("stun_next_round"));
    }
}

static void
on_destroy()
{
    on_move(environment(), 0);
}


public void
stun_next_round()
{
    object ply;
    if (!objectp(ply = environment()) || !living(ply) ||
        ply->query_dead() || --_duration <= 0)
    {
        destroy();
        return;
    }
    ply->set_busy_next_round();
}

public void
set_duration(int val)
{
    _duration = val;
}

public void
add_duration(int val)
{
    _duration += val;
}

public int
query_duration()
{
    return _duration;
}
