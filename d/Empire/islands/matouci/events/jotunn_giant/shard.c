#include "/d/Empire/empire.h"

#define EVENT_NUM_WAVES        5
#define EVENT_BEATS_PER_WAVE   10

inherit EMP_I_ITEM;

private string *_noise;
private object  _ply;
private int     _wave;
private int     _beat;

static void 
create() 
{
    ::create();
    _noise = ({ 
        "You hear a pig squeal nearby.",
        "There is something approaching.",
        "You hear something running around nearby.",
        "You see something moving just off the path.",
        "There is a large THUD nearby.",
        "The canopy of the surrounding trees sway back and forth.",
        "You hear the sound of a tree falling down.",
        "Something sails through the air overhead, dripping blood as it passes.",
        "%^BOLD%^The ground trembles.%^END%^",
        "%^BOLD%^There is something big approaching.%^END%^",
    });
    _ply  = 0;
    _wave = 0;
    _beat = 0;

    set_name("shard");
    set_short(0);
    set_get(NO_GET);
    set_heart_beat(1);
}

private void
make_noise(int wave) 
{
    int idx, len;
    len = sizeof(_noise);
    idx = (wave * len) / EVENT_NUM_WAVES;
    idx = (idx - 2 + random(5));
    idx = idx < 0 ? 0 : (idx < len ? idx : len - 1);
    tell_room(environment(), _noise[idx] + "\n");
}

private void
spawn_wave(int wave) 
{
    int i;
    for (i = 0; i < wave; ++i) {
        make(resolve_path("pig"), environment());
    }
}

private void
spawn_boss() 
{
    make(resolve_path("giant"), environment());
}

public void
heart_beat() 
{
    object env;
    if (!objectp(env = environment()) || !objectp(_ply)) {
        destroy();
        return;
    } else if (!objectp(present(_ply, env))) {
        EMP_D_LOG->log("event", "Roasted pigs owner is gone, aborting..");
        destroy();
        return;
    } 
    if (++_beat < EVENT_BEATS_PER_WAVE) {
        make_noise(_wave);
        return;
    }
    if (++_wave < EVENT_NUM_WAVES) {
        EMP_D_LOG->log("event", "Roasted pig wave " + _wave + " spawned.");
        spawn_wave(_wave);
        _beat = 0;
        return;
    }    
    EMP_D_LOG->log("event", "Roasted pig boss spawned.");
    spawn_boss();
    destroy();
}

public void
set_player(object val) 
{
    _ply = val;
}
