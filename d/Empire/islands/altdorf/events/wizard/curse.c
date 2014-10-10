#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ARMOUR;

static void
create()
{
    ::create();
    set_name("magical curse");
    set_short(0);
    set_type("aura");
    add_property("tagged");
    add_property("unremovable");
    add_property("protected",100);
    set_weight(0);
    set_drop(NO_DROP);

    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));

    destroy(30 + random(30));
}

static void
on_move(object from, object to)
{
    if (objectp(from) && living(from)) {
        tell_object(from, "You no longer feel sick.\n");
        from->remove_hook("__heart_beat");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "You feel sick!\n");
        to->add_hook("__heart_beat", store_fp("on_wearer_heart_beat"));
        wear(1);
    }
}

static void
on_destroy()
{
    on_move(environment(), 0);
}

public string
extra_look()
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return 0;
    }
    return capitalize(ply->query_pronoun() + " is surrounded " +
                      "by a swarm of flies");
}

private void
throw_up() {

    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->command("puke");
    ply->reduce_hit_point(50 + random(50));
}

private void
unwield_all()
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->command("shiver");
    ply->command("unwield all");
}

public void
on_wearer_heart_beat()
{
    switch (random(10)) {
    case 0:
        throw_up();
        break;
    case 1:
        unwield_all();
        break;
    }
}
