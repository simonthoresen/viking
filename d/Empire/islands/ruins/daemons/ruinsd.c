#include "/d/Empire/islands/ruins.h"

#define COOLDOWN_SECS   (3600*24*7)
#define SAVE_FILE       (EMP_DIR_VAR + "ruinsd")

inherit EMP_I_DAEMON;

public  int     _reset_at;
public  mapping _is_dead;
private mapping _npcs;

static void
create()
{
    ::create();
    _reset_at = 0;
    _is_dead  = ([ ]);
    _npcs     = ([ ]);
}

public void
reset(int not_first)
{
    ::reset(not_first);
    if (!not_first) {
        restore_object(SAVE_FILE);

        // _P_A_R_A_N_O_I_A_
        if (!mapp(_is_dead)) {
            _is_dead = ([ ]);
        }
    }
}

public void
register_death(object corpse, object killer)
{
    if (_reset_at <= time()) {
        // there is currently no cooldown, meaning this must be the first kill
        // in a new period. schedule a reset after configured cooldown
        _reset_at = time() + COOLDOWN_SECS;
    }
    _is_dead[source_file_name(previous_object())] = time();
    save_object(SAVE_FILE);
}

public int
can_spawn(string src)
{
    if (objectp(_npcs[src])) {
        return 0;
    }
    if (_reset_at > time() && _is_dead[src]) {
        return 0;
    }
    return 1;
}

public object
try_spawn(string src)
{
    object obj;
    if (!can_spawn(src)) {
        return 0;
    }
    obj = new(src);
    obj->add_hook("__die", store_fp("register_death"));
    _npcs[src] = obj;
    return obj;
}

public object
query_npc(string src)
{
    return _npcs[src];
}
