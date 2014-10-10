#include "/d/Empire/islands/matouci.h"

inherit EMP_I_MONSTER;

private object *_globs;
private int     _progress;
private int     _silent;

static void
create() 
{
    ::create();
    _globs    = 0;
    _progress = 0;
    _silent   = 0;

    set_name("Glob of Jormungand");
    set_short("a glob of Jormungand");
    set_long("This is a small glob of organic matter.");
    add_id(({ "glob", "jormungand" }));
    set_log_file("jormungand");
    set_no_corpse(1);
    set_level(25);
    set_aggressive(1);
    set_hp(1000);
    set_ac(10);
    set_wc(33);
    add_property("unarmed_damage_type", ({ "acid", "magic" }));

    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__bdie", store_fp("on_bdie"));
}

private string
query_noise() 
{
    switch (_progress) {
    case 0:
        return "The globs begin to move.";
    case 1:
        return "The globs are moving towards each other.";
    case 2:
        return "The globs are slowly coming together.";
    case 3:
        return "The globs are forming a larger pulp of organic matter.";
    case 4:
        return "The pulp of blood and gore is growing.";
    case 5:
        return "%^BOLD%^The eye of Jormungand appears in the pulp.%^END%^";
    case 6:
        return "The body of Jormungand is growing out of the organic pulp.";
    case 7:
        return "%^BOLD%^The mouth of Jormungand opens into the bloody " +
	       "pulp.%^END%^";
    case 8:
        return "The body of blood and gore is becoming Jormungand.";
    case 9:
        return "%^B_RED%^%^L_YELLOW%^Jormungand awakens!%^END%^";
    }
    return 0;
}

private int
check_progress() 
{
    object env;
    if (!objectp(env = environment()) ||
	!arrayp(_globs) ||
	sizeof(_globs -= ({ 0 })) == 0) 
    {
	return 0;
    }
    if (!_silent) {
        string str;
        _globs->set_silent(1);
        if (stringp(str = query_noise())) {
            tell_room(env, str + "\n");
        }
    }
    _silent = 0;
    return ++_progress > 9;
}

static void
on_heart_beat() 
{
    object env, obj, *arr;
    if (!objectp(env = environment()) ||
	!check_progress()) 
    {
        return;
    }
    make(resolve_path("serpent"), env)->set_num_globs(sizeof(_globs));
    (_globs - ({ this_object() }))->destroy();
    destroy();
}

static int
on_bdie(object foe) 
{
    return arrayp(_globs) && sizeof(_globs) == 1;
}

public void
set_silent(int val) 
{
    _silent = val;
}

public int
query_silent() 
{
    return _silent;
}

public void
set_progress(int val) 
{
    _progress = val;
}

public int
query_progress() 
{
    return _progress;
}

public void
set_globs(object *val) 
{
    _globs = val;
}

public object *
query_globs() 
{
    return _globs;
}

public int
is_jormungand_glob() 
{
    return 1;
}
