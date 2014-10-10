#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER_BASE;

private int _last_beat;
private int _bored_secs;

static void
create() 
{
    ::create();
    _last_beat  = time();
    _bored_secs = 0;
}

public void 
create_done()
{
    ::create_done();
    if (_bored_secs <= 0) {
        return;
    }
    add_hook("__heart_beat", store_fp("not_bored"));
    call_out("check_bored", 0);
}

public nomask void 
check_bored() 
{
    object env;
    if (objectp(query_attack()) || _last_beat > time() - _bored_secs) {
        call_out("check_bored", 60);
        return;
    }
    if (objectp(env = bottom_room())) {
        tell_room(env, query_name() + " leaves out of boredom.\n");
    }
    destruct(this_object());
}

static nomask void
not_bored() 
{
    _last_beat = time();
}

public nomask void
set_last_beat(int val) 
{
    _last_beat = val;
}

public nomask int
query_last_beat() 
{
    return _last_beat;
}

public nomask void
set_bored_secs(int val) 
{
    if (is_create_done()) {
        error("set_bored_secs() must be called in create()");
    }
    _bored_secs = val;
}

public nomask int
query_bored_secs() 
{
    return _bored_secs;
}
