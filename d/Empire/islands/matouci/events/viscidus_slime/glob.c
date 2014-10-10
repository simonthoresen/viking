#include "/d/Empire/empire.h"

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

    set_name("Glob of Viscidus");
    set_short("a glob of Viscidus");
    set_long("This is a small glob of green slime.");
    add_id(({ "glob", "viscidus" }));
    set_level(19);
    set_hp(250);

    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__bdie", store_fp("on_bdie"));
}

private string
query_noise() 
{
    switch (_progress) {
    case 0: return "The globs begin to move.";
    case 1: return "The globs are moving towards each other.";
    case 2: return "The globs are slowly coming together.";
    case 3: return "The globs are forming a larger puddle of slime.";
    case 4: return "The puddle of slime is growing.";
    case 5: return "%^BOLD%^The eye of Viscidus appears in the slime.%^END%^";
    case 6: return "The body of Viscidus is growing out of the slime.";
    case 7: return "%^BOLD%^The mouth of Viscidus opens into the slime.%^END%^";
    case 8: return "The body of slime is becoming Viscidus.";
    case 9: return "%^B_GREEN%^%^BLACK%^Viscidus awakens!%^END%^";
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
    object env;
    if (!objectp(env = environment()) ||
	!check_progress()) 
    {
        return;
    }
    make(resolve_path("slime"), env)->set_num_globs(sizeof(_globs));
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
is_viscidus_glob() 
{
    return 1;
}
