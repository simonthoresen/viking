#include "/d/Artifact/artifact.h"

inherit ART_I_SLIVER;

private int _train_cost;
private int _cast_cost;
private int _cooldown;
private int _duration;

static void
create()
{
    string name;
    ::create();
    _train_cost  = 0;
    _cast_cost   = 0;
    _cooldown    = 0;
    _duration    = 0;

    set_type("spell");
    set_slot("spell", -1);
    if (query_rank() > 1) {
        add_spell_req(query_base_name() + "_" + (query_rank() - 1));
    }
}

static void
setup_player(object ply)
{
    ::setup_player(ply);
    if (!objectp(ply)) {
        return;
    }
    if (_duration >= 0) {
        call_out("expire_sliver", _duration);
    }
    ply->set_tmp_prop(ART_P_SPELL(this_object()), time() + _cooldown);
    ply->reduce_spell_point(_cast_cost);

    ART_D_QUEST->add_unlock(ply, "cast_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "cast_100", 1, 100);
    ART_D_QUEST->add_unlock(ply, "cast_1000", 1, 1000);
    ART_D_QUEST->add_unlock(ply, "cast_10000", 1, 10000);
}

static varargs nomask void
fizzle_spell(string str)
{
    if (!stringp(str)) {
        str = "Your spell fizzles and dies.";
    }
    message_player("", str + "\n");
    destroy_later();
}

public nomask int
query_ready_secs(object ply)
{
    int val;
    if (!objectp(ply)) {
        return 0;
    }
    val = ply->query_tmp_prop(ART_P_SPELL(this_object())) - time();
    return val > 0 ? val : 0;
}

public int
can_use(object ply, object wpn)
{
    int val;
    if (!::can_use(ply, wpn)) {
        return 0;
    }
    if (!objectp(wpn)) {
        return 1;
    }
    if (!ply->query_property(ART_P_SPELL(this_object()))) {
        return notify_fail("You do not know this spell.");
    }
    if (ply->query_sp() < _cast_cost) {
        return notify_fail("Insufficient spell points (" + _cast_cost +
                           " required).");
    }
    if ((val = query_ready_secs(ply)) > 0) {
        return notify_fail("Is is on cooldown (" + val +
                           " seconds remaining).");
    }
    return 1;
}

public nomask int
query_expire_secs()
{
    return find_call_out("expire_sliver");
}

public nomask void
expire_sliver()
{
    destroy();
}

public nomask void
set_train_cost(int val)
{
    _train_cost = val;
}

public nomask int
query_train_cost()
{
    return _train_cost;
}

public nomask void
set_cast_cost(int val)
{
    _cast_cost = val;
}

public nomask int
query_cast_cost()
{
    return _cast_cost;
}

public nomask void
set_cooldown(int val)
{
    _cooldown = val;
}

public nomask int
query_cooldown()
{
    return _cooldown;
}

public nomask void
set_duration(int val)
{
    _duration = val;
}

public nomask int
query_duration()
{
    return _duration;
}
