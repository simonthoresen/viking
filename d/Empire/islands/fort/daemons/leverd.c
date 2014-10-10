#include "/d/Empire/islands/fort.h"

#define TIME_OPEN   (10)

inherit I_DAEMON;

private mapping _levers;
private int     _tick;

static void
create()
{
    ::create();
    _levers = ([ ]);
    _tick   = 0;
}

public int
num_levers()
{
    int i, len, *arr, ret;
    for (i = 0, len = sizeof(arr = map_values(_levers)), ret = 0;
         i < len; ++i)
    {
        if (arr[i] + TIME_OPEN < time()) {
            continue;
        }
        ++ret;
    }
    return ret;
}

public int
pull_lever(string entry)
{
    if (!FOR_D_GATE->can_open()) {
        return 0;
    }
    if (num_levers() == 0) {
        set_heart_beat(1);
    }
    _levers[entry] = time();
    return 1;
}

public void
heart_beat()
{
    int val;
    if ((val = num_levers()) == 0) {
        set_heart_beat(0);
    } else if (val < FOR_NUM_WINGS) {
        FOR_ISLAND->tell_island((++_tick % 2) ? "... tick ...\n" :
                                "... tock ...\n");
    } else if (val == FOR_NUM_WINGS) {
        _levers = ([ ]);
        FOR_D_GATE->open_gauntlet();
    }
}
