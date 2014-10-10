#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER_GREETING;

private string _log_file;

static void
create() 
{
    ::create();
    _log_file = 0;

    add_hook("__die", store_fp("log_die"));
    add_hook("__kill", store_fp("log_kill"));
}

static nomask void
log_die(object corpse, object killer) 
{
    object victim;
    if (!objectp(victim = previous_object()) || 
	!objectp(killer) || 
	!interactive(killer) ||
	wizardp(killer))
    {
        return;
    }
    EMP_D_LOG->log(stringp(_log_file) ? _log_file : "die", 
                   sprintf("%s (%d) killed %s (%d)", 
                           killer->query_real_name(),
                           killer->query_level(),
                           victim->query_real_name(), 
                           victim->query_level()));
}

static nomask void
log_kill(object victim, object killer) 
{
    if (!objectp(victim) || 
	!objectp(killer) ||
	!interactive(victim) ||
	wizardp(victim))
    {
        return;
    }
    EMP_D_LOG->log(stringp(_log_file) ? _log_file : "kill", 
                   sprintf("%s (%d) killed %s (%d)", 
                           killer->query_real_name(),
                           killer->query_level(),
                           victim->query_real_name(), 
                           victim->query_level()));
}

public nomask void
set_log_file(string val) 
{
    _log_file = val;
}

public nomask string
query_log_file() 
{
    return _log_file;
}
