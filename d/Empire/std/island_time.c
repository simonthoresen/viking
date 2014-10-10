#include "/d/Empire/empire.h"

inherit EMP_I_ISLAND_LIVINGS;

private int _time;
private int _weather;

static void 
create() 
{
    ::create();
    _time    = EMP_D_TIME->query_hour_of_day();
    _weather = EMP_D_WEATHER->query_tick(); 
    add_hook("__heart_beat", store_fp("check_time"));
}

private void 
notify_change(string *desc) 
{
    object *arr;
    int i, len;
    if (!arrayp(desc)) {
        return;
    }
    for (i = 0, len = sizeof(arr = query_livings()); i < len; ++i) {
        object obj, env;
        string str;
        if (!objectp(obj = arr[i]) ||
            !objectp(env = environment(obj)) ||
            env->query_property("underground") ||
            env->query_property("under_water") ||
            !stringp(str = desc[env->query_property("indoors") ? 0 : 1]))
        {
            continue;
        }
        tell_object(obj, str + "\n");
    }    
}

private string 
desc_time(int hour_of_day) 
{
    switch (hour_of_day) {
    case 6:  return "The sun is slowly ascending behind the horizon.";
    case 7:  return "The sun rises.";
    case 14: return "The sun climbs to zenith. It is midday."; 
    case 18: return "The sun is slowly descending. Soon it will be dusk.";
    case 19: return "It is now dusk. The sky turns darker.";
    case 21: return "The sun is setting. It will be night soon.";
    case 22: return "The sun sets in the horizon. Night is imminent.";
    case 23: return "The sky goes dark. It is night.";
    default: return 0;
    }
}

static nomask void 
check_time() 
{
    int val;
    if ((val = EMP_D_TIME->query_hour_of_day()) != _time) {
        notify_change(({ 0, desc_time(val) }));
        _time = val;
    }
    if ((val = EMP_D_WEATHER->query_tick()) != _weather) {
        notify_change(EMP_D_WEATHER->query_change());
        _weather = val;
    }
}
