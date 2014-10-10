#include "/d/Empire/empire.h"

inherit EMP_I_DAEMON;

public int      expected_cloud();
public int      expected_rain();
public int      expected_mist();
public int      expected_wind();
public int      expected_temp();
private string *desc_weather();

private int     _cloud;
private int     _rain;
private int     _mist;
private int     _wind;
private int     _temp;
private string *_weather;
private string *_change;
private int     _tick;

static void
create()
{
    ::create();
    _cloud   = expected_cloud();
    _rain    = expected_rain();
    _mist    = expected_mist();
    _wind    = expected_wind();
    _temp    = expected_temp();
    _weather = desc_weather();
    _change  = 0;
    _tick    = 0;
    set_heart_beat(1);
}

private void
change_var(string name)
{
    int val, exp, add;
    val = call_other(this_object(), "query_" + name);
    exp = call_other(this_object(), "expected_" + name);
    if (val < exp) {
        add = 1 + random(10);
    } else if (val == exp) {
        add = (random(2) ? -1 : 1) * (1 + random(10));
    } else if (val > exp) {
        add = -(1 + random(10));
    }
    call_other(this_object(), "set_" + name, val + add);
}

public void
heart_beat()
{
    if (random(100) > 1) {
        return;
    }
    change_var(({ "cloud", "rain", "mist", "wind", "temp" })[random(5)]);
}

public int
expected_cloud()
{
    switch (EMP_D_TIME->query_season()) {
    case EMP_SEASON_SPRING: return 5;
    case EMP_SEASON_SUMMER: return 20;
    case EMP_SEASON_AUTUMN: return 80;
    case EMP_SEASON_WINTER: return 70;
    }
}

public int
expected_rain()
{
    switch (EMP_D_TIME->query_season()) {
    case EMP_SEASON_SPRING: return 5;
    case EMP_SEASON_SUMMER: return 20;
    case EMP_SEASON_AUTUMN: return 60;
    case EMP_SEASON_WINTER: return 80;
    }
}

public int
expected_mist()
{
    switch (EMP_D_TIME->query_season()) {
    case EMP_SEASON_SPRING: return 70;
    case EMP_SEASON_SUMMER: return 20;
    case EMP_SEASON_AUTUMN: return 40;
    case EMP_SEASON_WINTER: return 10;
    }
}

public int
expected_wind()
{
    switch (EMP_D_TIME->query_season()) {
    case EMP_SEASON_SPRING: return 40;
    case EMP_SEASON_SUMMER: return 50;
    case EMP_SEASON_AUTUMN: return 60;
    case EMP_SEASON_WINTER: return 70;
    }
}

public int
expected_temp()
{
    switch (EMP_D_TIME->query_season()) {
    case EMP_SEASON_SPRING: return 60;
    case EMP_SEASON_SUMMER: return 80;
    case EMP_SEASON_AUTUMN: return 25;
    case EMP_SEASON_WINTER: return 5;
    }
}

public string
desc_mist()
{
    switch (_mist) {
    case  0..33: return 0;
    case 34..66: return "a light mist dims your sight";
    case 67..99: return "a heavy fog obscures your sight";
    }
}

public string
desc_sky()
{
    string str;
    str = "";
    if (_cloud >= 10) {
        switch (_cloud) {
        case 10..39: str = "a few clouds are "; break;
        case 40..69: str = "clouds are "; break;
        case 70..99: str = "heavy clouds are "; break;
        }
        switch (_wind) {
        case  0..19: str += "still in "; break;
        case 20..39: str += "slowly moving across "; break;
        case 40..59: str += "moving across "; break;
        case 60..79: str += "rolling across "; break;
        case 80..99: str += "racing across "; break;
        }
    }
    str += "the ";
    switch (_temp) {
    case  0..24: str += "cold "; break;
    case 25..49: str += "chilly "; break;
    case 50..74: str += "warm "; break;
    case 75..99: str += "hot "; break;
    }
    if (EMP_D_TIME->is_night()) {
        str += "night ";
    }
    str += "sky";
    if (_cloud < 10) {
        str += " is clear";
    }
    return str;
}

public string
desc_light()
{
    if (EMP_D_TIME->is_night()) {
        if (_mist > 66 || _cloud >= 70) {
            return "darkness";
        }
	if(_cloud >= 40) {
            return "dim moonlight";
        }
        if (abs(15 - EMP_D_TIME->query_day_of_month()) < 2) {
            return "bright moonlight";
        }
	return "moonlight";
    } else {
        if (_cloud >= 40) {
            return "dim sunlight";
        }
        if (EMP_D_TIME->query_season() == EMP_SEASON_SUMMER) {
            return "bright sunlight";
        }
        if (EMP_D_TIME->is_morning() || EMP_D_TIME->is_evening()) {
            return "golden sunlight";
        }
        return "sunlight";
    }
}

public string
desc_roof()
{
    if (_temp < 33) {
        switch (_rain) {
        case  0..19: return 0;
        case 20..59: return "occasional thuds sound from above";
        case 60..99: return "thuds sound from above";
        }
    } else {
        switch (_rain) {
        case  0..19: return 0;
        case 20..59: return "you hear pattering sounds from above";
        case 60..99: return "a continuous drumming noise sounds from above";
        }
    }
}

public string
desc_wind()
{
    switch (_wind) {
    case  0.. 9: return 0;
    case 10..19: return "a light breeze stirs the air";
    case 20..29: return "a gentle breeze stirs the air";
    case 30..39: return "a moderate breeze stirs the air";
    case 40..49: return "a fresh breeze blows around you";
    case 50..59: return "a strong breeze blows around you";
    case 60..69: return "there is a moderate gale";
    case 70..79: return "there is a fresh gale";
    case 80..89: return "there is a strong gale";
    case 90..99: return "you brace yourself against the whole gale";
    }
}

public string
desc_rain()
{
    string str;
    if (_temp < 20) {
        str = "snowing";
    } else if (_temp < 30) {
        str = "hailing";
    } else {
        str = "raining";
    }
    switch (_rain) {
    case  0..19: return 0;
    case 20..39: return "it is " + str + " lightly";
    case 40..59: return "it is " + str + " moderately";
    case 60..79: return "it is " + str + " heavily";
    case 80..99: return "it is " + str + " violently";
    }
}

private string *
desc_weather()
{
    string *in, *out;
    in  = ({ "outside, " + desc_sky() }) +
          ({ desc_rain() }) +
          ({ desc_roof() }) +
          ({ desc_light() + " streams into the room" });
    out = ({ desc_sky() }) +
          ({ desc_rain() }) +
          ({ "there is " + desc_light() }) +
          ({ desc_mist() }) +
          ({ desc_wind() });
    return ({ capitalize(make_list(in  - ({ 0 })) + "."),
              capitalize(make_list(out - ({ 0 })) + ".") });
}

private string *
desc_change(string *val)
{
    if (!arrayp(val)) {
        return 0;
    }
    return ({ stringp(val[0]) ? capitalize(val[0]) + "." : 0,
              stringp(val[1]) ? capitalize(val[1]) + "." : 0 });
}

public string
change_cloud(int prev, int next)
{
    if (next > prev) {
        if (next >= 10 && prev < 10) {
            return "a few clouds appear on the sky";
        } else if (next >= 40 && prev < 40) {
            return "it is starting to cloud over";
        } else if (next >= 70 && prev < 70) {
            return "the cloud cover gets heavier";
        }
    } else if (next < prev) {
        if (next < 10 && prev >= 10) {
            return "the sky clears";
        } else if (next < 40 && prev >= 40) {
            return "the clouds begin to break up";
        } else if (next < 70 && prev >= 70) {
            return "the cloud cover decreases";
        }
    }
    return 0;
}

public string
change_rain(int prev, int next)
{
    string str;
    switch (_temp) {
    case  0..19: str = "snow"; break;
    case 20..29: str = "hail"; break;
    case 30..99: str = "rain"; break;
    }
    if (next > prev) {
        if (prev < 20) {
            if (next >= 20) {
                return "it starts to " + str;
            }
        } else if (prev / 5 != next / 5) {
            return "the " + str + " gets heavier";
        }
    } else if (next < prev) {
        if (prev >= 20) {
            if (next < 20) {
                return "the " + str + "ing stops";
            }
        } else if (prev / 5 != next / 5) {
            return "the " + str + " eases up";
        }
    }
    return 0;
}

public string
change_roof(int prev, int next)
{
    string str;
    if (!stringp(str = change_rain(prev, next))) {
        return 0;
    }
    str = "outside " + str + ", and ";
    if (next > prev) {
        if (prev < 20) {
            return str + "you hear a thudding noise on the roof";
        }
        return str + "the thudding on the roof increases";
    } else if (next < prev) {
        if (next < 20) {
            return str + "the thudding noise on the roof stops";
        }
        return str + "the thudding noise on the roof decreases";
    }
    return 0;
}

public string
change_mist(int prev, int next)
{
    if (next > prev) {
        if (next > 33 && prev <= 33) {
            return "a fine mist settles all around";
        } else if (next > 66 && prev < 66) {
            return "the mist thickens to a heavy fog";
        }
    } else if (next < prev) {
        if (next <= 33 && prev > 33) {
            return "the fine mist clears";
        } else if (next <= 66 && prev > 66) {
            return "the fog thins to a fine mist";
        }
    }
}

public string
change_wind(int prev, int next)
{
    if (next < prev) {
        if (next < 10 && prev >= 10) {
            return "the light breeze stills";
        }
        if (next / 10 != prev / 10) {
            return "the wind is easing off";
        }
    } else if (next > prev) {
        if (next >= 10 && prev < 10) {
            return "a light breeze sets in";
        }
        if (next / 10 != prev / 10) {
            return "the wind is picking up";
        }
    }
    return 0;
}

public string
change_temp(int prev, int next)
{
    if (prev / 10 != next / 10) {
        if (prev < next) {
            return "it is getting warmer";
        }
        if (next < prev) {
            return "it is getting colder";
        }
    }
    return 0;
}

public int
query_cloud()
{
    return _cloud;
}

public void
set_cloud(int val)
{
    string arg;
    val = max(0, min(99, val));
    if (stringp(arg = change_cloud(_cloud, val))) {
        _change = desc_change(({ "outside, " + arg, arg }));
        ++_tick;
    }
    _cloud = val;
    _weather = desc_weather();
}

public int
query_rain()
{
    return _rain;
}

public void
set_rain(int val)
{
    string arg1, arg2;
    val  = max(0, min(99, val));
    arg1 = change_roof(_rain, val);
    arg2 = change_rain(_rain, val);
    if (stringp(arg1) || stringp(arg2)) {
        _change = desc_change(({ arg1, arg2 }));
        ++_tick;
    }
    _rain = val;
    _weather = desc_weather();
}

public int
query_mist()
{
    return _mist;
}

public void
set_mist(int val)
{
    string arg;
    val = max(0, min(99, val));
    if (stringp(arg = change_mist(_mist, val))) {
        _change = desc_change(({ "outside, " + arg, arg }));
        ++_tick;
    }
    _mist = val;
    _weather = desc_weather();
}

public int
query_wind()
{
    return _wind;
}

public void
set_wind(int val)
{
    string arg;
    val = max(0, min(99, val));
    if (stringp(arg = change_wind(_wind, val))) {
        _change  = desc_change(({ "outside, " + arg, arg }));
        ++_tick;
    }
    _wind = val;
    _weather = desc_weather();
}

public int
query_temp()
{
    return _temp;
}

public void
set_temp(int val)
{
    string arg;
    val = max(0, min(99, val));
    if (stringp(arg = change_temp(_temp, val))) {
        _change = desc_change(({ 0, arg }));
        ++_tick;
    }
    _temp = val;
    _weather = desc_weather();
}

public string *
query_weather()
{
    return _weather;
}

public string *
query_change()
{
    return _change;
}

public int
query_tick()
{
    return _tick;
}
