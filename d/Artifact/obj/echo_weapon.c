#include "/d/Artifact/artifact.h"

inherit I_MONSTER;

private object _weapon;

static void
create()
{
    ::create();
    _weapon = 0;

    set_long(store_fp("my_long"));
    add_cmdpath(ART_DIR_COM + "b/");
    add_cmdpath(EMP_DIR_COM_M);
    add_property(EMP_P_IGNORE);
    add_property("interactive_monster");
    add_property("no_nothing");
    add_property("no_party");
    add_hook("__bdie", store_fp("on_bdie"));
    add_hook("__bnotify_attack", store_fp("on_bnotify_attack"));
    add_hook("__catch_tell", store_fp("on_catch_tell"));
    add_hook("__enter_inv", store_fp("on_enter_inv"));
    add_hook("__add_money", store_fp("on_add_money"));
}

public void
set_weapon(object obj)
{
    object ply;
    if (objectp(obj) && objectp(ply = obj->query_player())) {
        set_name(ply->query_real_name());
        set_short(0);
        set_gender(ply->query_gender());
    }
    _weapon = obj;
}

public object
query_weapon()
{
    return _weapon;
}

public object
query_player()
{
    return objectp(_weapon) ? _weapon->query_player() : 0;
}

private varargs mixed
call_player(string fnc, mixed args...)
{
    object obj;
    if (!objectp(obj = query_player())) {
        return 0;
    }
    return call_other(obj, fnc, args...);
}

public object
query_owner()
{
    return objectp(_weapon) ? _weapon->query_owner() : 0;
}

public object
query_user()
{
    return objectp(_weapon) ? _weapon->query_user() : 0;
}

public void
receive_message(mixed class, string msg)
{
    /* ::receive_message() will call __catch_tell without message class, and */
    /* some messages are passed directly to the hook. We catch as much as we */
    /* can here, and use the hook for the stuff that falls through.          */
    if (!objectp(_weapon)) {
        return;
    }
    _weapon->echo_message(class, msg);
}

static int
do_glance()
{
    /* For some reason /std/living.c has an action for glance that calls     */
    /* directly into /com/g/look.c. By returning 0 here we fall back to the  */
    /* command resolution instead.                                           */
    return 0;
}

public int
query_echo()
{
    return testbit(PLAYER_ECHO);
}

public int
command(string arg)
{
    object env;
    if (geteuid(previous_object()) != geteuid() &&
        origin() != ORIGIN_DRIVER &&
        origin() != ORIGIN_LOCAL)
    {
        return 0;
    }
    if (objectp(env = environment()) && env->query_exit(arg)) {
        return 0;
    }
    return ::command(arg);
}

public varargs int
move(mixed to)
{
    if (geteuid(previous_object()) != geteuid() &&
        origin() != ORIGIN_DRIVER &&
        origin() != ORIGIN_LOCAL)
    {
        return 0;
    }
    return ::move(to);
}

public varargs void
move_player(string dir, mixed to, int no_glance)
{
    if (geteuid(previous_object()) != geteuid() &&
        origin() != ORIGIN_DRIVER &&
        origin() != ORIGIN_LOCAL)
    {
        return;
    }
    ::move_player(dir, to, no_glance);
}

public varargs int
hit_player(int dmg, string type, object foe, string loc, object wpn)
{
    map_array(query_attackers(), "remove_attackers");
    if (objectp(foe)) {
        foe->remove_attackers(this_object());
    }
    return 0;
}

public object
query_attack()
{
    object usr;
    if (!objectp(usr = query_user())) {
        return 0;
    }
    return usr->query_attack();
}

public int
testbit(int bit)
{
    object ply;
    if (!objectp(ply = query_player())) {
        return ::testbit(bit);
    }
    return ply->testbit(bit);
}

public mapping
query_m_property()
{
    mapping dat;
    object ply;
    dat = ::query_m_property();
    if (objectp(ply = query_player())) {
        dat += ply->query_m_property();
    }
    return dat;
}

public int
query_width()
{
    return call_player("query_width");
}

public void
set_width(int val)
{
    call_player("set_width", val);
}

public int
query_hp()
{
    return call_player("query_hp");
}

public int
query_max_hp()
{
    return call_player("query_max_hp");
}

public int
reduce_hit_point(int val)
{
    return call_player("reduce_hit_point", val);
}

public int
query_sp()
{
    return call_player("query_sp");
}

public int
query_max_sp()
{
    return call_player("query_max_sp");
}

public int
restore_spell_points(int val)
{
    return call_player("restore_spell_points", val);
}

static void
my_long(string arg, int nonl)
{
    object wpn, ply;
    string str;
    if (!objectp(wpn = query_weapon())) {
        return;
    }
    wpn->long(0, nonl);
    if (!objectp(ply = environment(wpn)) ||
        !living(ply) ||
        ply == this_player())
    {
        return;
    }
    if (!wpn->query_wielded()) {
        str = capitalize(ply->query_name()) + " is carrying " +
              query_objective() + ".";
    } else if (wpn->query_type() == "twohanded") {
        str = capitalize(ply->query_name()) + " is wielding " +
              query_objective() + " in both hands.";
    } else {
        str = capitalize(ply->query_name()) + " is wielding " +
              query_objective() + " in " + ply->query_possessive() + " " +
              wpn->query_hand() + ".";
    }
    write((nonl ? "\n" : "") + str + (nonl ? "" : "\n"));
}

private void
drop_later(string arg)
{
    call_out("command", 0, "drop " + arg);
}

static void
on_add_money(int val)
{
    drop_later(val + " coins");
}

static void
on_enter_inv(object obj, object from)
{
    drop_later("all");
}

static int
on_bnotify_attack(object foe)
{
    return 1;
}

static int
on_bdie(object foe)
{
    return 1;
}

static void
on_catch_tell(string msg)
{
    receive_message("", msg);
}
