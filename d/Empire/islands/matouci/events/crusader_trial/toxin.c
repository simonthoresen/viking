#include "/d/Empire/empire.h"

inherit EMP_C_LIQUID;

static void
create() 
{
    ::create();
    set_name("paralyzing toxin");
    set_color("%^GREEN%^");
    set_long("It is a highly paralyzing toxin.");
    add_id("toxin");
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__move", store_fp("on_move"));
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && living(from)) {
        tell_object(from, "Your are no longer paralyzed!\n");
        from->remove_hook("__battack");
        from->remove_hook("__bmove_player");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "YOU ARE PARALYZED!\n");
        to->add_hook("__battack", store_fp("prevent_action"));
        to->add_hook("__bmove_player", store_fp("prevent_action"));
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public int
prevent_action() 
{
    object ply;
    if (!objectp(ply = previous_object()) ||
        ply->query_property(EMP_P_NOSTUN))
    {
        return 0;
    }
    tell_object(ply, "You are paralyzed!\n");
    return 1;
}
