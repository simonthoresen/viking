#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ARMOUR;

static void
create()
{
    ::create();
    set_name("magical wisdom");
    set_short(0);
    set_type("aura");
    add_property("tagged");
    add_property("unremovable");
    add_property("protected",100);
    set_weight(0);
    set_drop(NO_DROP);
    set_wear_modifier("int", 1, 4);
    set_light(1);

    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));

    destroy(120 + random(1200));
}

static void
on_move(object from, object to)
{
    if (objectp(from) && living(from)) {
        tell_object(from, "You feel dumb again.\n");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "You feel wise.\n");
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
                      "by a halo of wisdom");
}
