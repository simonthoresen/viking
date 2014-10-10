#include "/d/Artifact/artifact.h"

inherit EMP_I_ITEM;

private object _weapon;

static void
create()
{
    ::create();
    _weapon = 0;

    set_name("soulstone");
    set_short(0);
    add_id(source_file_name());
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
    add_trigger("pray", store_fp("do_pray"));
}

public int
drop(int silent)
{
    return NO_DROP;
}

public void
init_arg(string arg)
{
    /* empty */
}

static int
do_pray(string arg)
{
    object ply;
    ply = this_player();
    if (!ply->query_dead() || !environment(ply)<-R_SMITHY) {
        write("You hail Volund.\n");
        return 1;
    }
    ply->remove_ghost();
    return 1;
}

static void
on_move(object from, object to)
{
    if (objectp(from)) {
        from->remove_hook("__blong");
        from->remove_hook("__move");
        from->remove_hook("__set_dead");
    }
    if (objectp(to) && living(to)) {
        to->add_hook("__blong", store_fp("desc_weapon"));
        to->add_hook("__move", store_fp("force_ghost"));
        to->add_hook("__set_dead", store_fp("check_dead"));
    }
}

static void
on_destroy()
{
    if (objectp(_weapon)) {
        _weapon->destroy_later();
        _weapon = 0;
    }
    on_move(environment(), 0);
}

public int
desc_weapon(string arg)
{
    if (objectp(_weapon)) {
        _weapon->long();
    } else {
        write(previous_object()->short() + ".\n");
    }
    return 1;
}

private int
is_livable(object env)
{
    return geteuid(env) == geteuid() ||
           starts_with(source_file_name(env),
                       EMP_DIR_VAR_ISLANDS + "artifact/");
}

public void
force_ghost(object from, object to)
{
    object ply;
    if (!objectp(ply = previous_object()) ||
        !objectp(to))
    {
        return;
    }
    if (is_livable(to)) {
        if (ply->query_ghost()) {
            tell_object(ply, "You leave the realm of the dead.\n");
            ply->remove_ghost(1);
        }
    } else if (!ply->query_ghost()) {
        if (!wizardp(ply)) {
            tell_object(ply, "You enter the realm of the dead.\n");
            ply->set_ghost();
        } else {
            tell_object(ply, "Your wizardhood protects your from " +
                             "becoming a ghost.\n");
        }
    }
}

public void
check_dead(int dead)
{
    object ply, env;
    ply = previous_object();
    if (dead) {
        object wpn;
        if (!objectp(env = environment(ply)) ||
            !objectp(wpn = env->query_weapon()) ||
            !objectp(env = bottom_room(wpn)))
        {
            env = R_CHURCH->__bootstrap();
        }
        ply->move_player("x", env, 1);
    } else {
        if (!objectp(env = environment(ply)) ||
            !is_livable(env))
        {
            ply->move_player("x", ART_MASTER);
        }
    }
}

public void
set_weapon(object val)
{
    _weapon = val;
}

public object
query_weapon()
{
    return _weapon;
}

public object
get_instance(object ply)
{
    object gem;
    if (objectp(ply) &&
        objectp(gem = ply->query_property(ART_C_SOULSTONE)))
    {
        /* cache soulstone in a property to avoid having to */
        /* scan the player's directory on every query for   */
        /* soulstone or weapon -- it happens _very_ often   */
        return gem;
    }
    if (!ART_MASTER->is_member(ply)) {
        error(sprintf("expected guild member, got %O", ply));
    }
    if (!objectp(gem = present(ART_C_SOULSTONE, ply))) {
        gem = new(ART_C_SOULSTONE);
        gem->move(ply);
        ply->add_property(ART_C_SOULSTONE, gem);
    }
    return gem;
}
