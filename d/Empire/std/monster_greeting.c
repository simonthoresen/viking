#include "/d/Empire/empire.h"
#define P_GREETED ("greeted_by_" + source_file_name())

inherit EMP_I_MONSTER_FACTION;

private mixed  _greeting;
private object _greet_ply;
private int    _greet_idx;

static void
create() 
{
    ::create();
    _greeting  = 0;
    _greet_idx = 0;
    _greet_ply = 0;
}

public void
create_done()
{
    ::create_done();
    if (_greeting == 0) {
        return;
    }
    add_hook("__init", store_fp("check_greeting"));    
    add_hook("__peace_beat", store_fp("next_greeting"));
}

static nomask void
check_greeting() 
{
    object ply;
    if (objectp(_greet_ply) && objectp(present(_greet_ply, bottom_room()))) {
	return;
    }
    if (!objectp(ply = this_player()) ||
        !interactive(ply) || 
        ply->query_dead() ||
	ply->query_invis() ||
        ply->query_tmp_prop(P_GREETED))
    {
        return;
    }
    ply->set_tmp_prop(P_GREETED, 1);
    _greet_ply = ply;
    _greet_idx = 0;
}

private void
perform_greeting(mixed arg) 
{
    if (functionp(arg)) {
	arg = call_fp(arg, this_object(), _greet_ply);
    }
    if (!stringp(arg)) {
	return;
    }
    if (arg[0] == '*') {
	command(arg[1..strlen(arg) - 1]);
    } else {
	tell_room(bottom_room(), arg);
    }
}

static nomask void
next_greeting() 
{
    if (!objectp(_greet_ply) || !arrayp(_greeting)) {
	return;
    }
    if (!objectp(present(_greet_ply, bottom_room())) ||
	_greet_idx >= sizeof(_greeting)) 
    {
	_greet_ply = 0;
	return;
    }
    perform_greeting(_greeting[_greet_idx++]);
}

public nomask void
set_greeting(mixed val) 
{
    if (is_create_done()) {
        error("set_greeting() must be called in create()");
    }
    if (val != 0 && !arrayp(val)) {
	val = ({ val });
    }
    _greeting = val;
}

public nomask mixed
query_greeting() 
{
    return _greeting;
}
