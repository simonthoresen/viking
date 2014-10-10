#include "/d/Empire/empire.h"

inherit EMP_I_ROOM_CRUMB;

private string _day_long;
private string _night_long;
private string _area_long;

static void
create()
{
    ::create();
    _day_long   = 0;
    _night_long = 0;
    _area_long  = 0;

    ::set_long(store_fp("on_long"));
    set_light(1);
}

public string
query_desc_hour()
{
    switch (EMP_D_TIME->query_hour_of_day()) {
    case 23:
    case 0..1:   return "The night is still young.";
    case 2..4:   return "It's the middle of the night.";
    case 5:      return "The night is at its end.";
    case 6..7:	 return "The day is dawning.";
    case 8..13:  return "It is morning.";
    case 14..17: return "It's the middle of the day.";
    case 18:     return "The sun is descending.";
    case 19..20: return "It is dusk.";
    case 21..22: return "The sun is setting.";
    default:     return 0;
    }
}

public string
query_desc_item()
{
    switch (EMP_D_TIME->query_season()) {
    case 0:  return "It feels somewhat warm.";
    case 1:  return "It is very hot!";
    case 2:  return "It is wet.";
    case 3:  return "It is covered in snow.";
    default: return 0;
    }
}

private string
append_to(string str, string add)
{
    int len;
    if (!stringp(str) || (len = strlen(str)) == 0) {
        return add;
    } else if (!stringp(add)) {
        return str;
    } else if (str[len - 1] == '\n') {
        return str + add;
    } else {
        return str + " " + add;
    }
}

public string
query_desc_long()
{
    string *arr, out;
    if (EMP_D_TIME->is_day()) {
        out = _day_long;
    } else {
        out = _night_long;
    }
    out = append_to(out, _area_long);
    if (!arrayp(arr = EMP_D_WEATHER->query_weather())) {
        arr = ({ 0, 0 });
    }
    if (query_property("underground") ||
        query_property("under_water"))
    {
        /* empty */
    } else if (query_property("indoors")) {
        out = append_to(out, arr[0]);
    } else {
        out = append_to(out, query_desc_hour());
        out = append_to(out, arr[1]);
    }
    return out;
}

public string
query_item_sun()
{
    switch (EMP_D_TIME->query_hour_of_day()) {
    case 6..9:   return "The sun is rising, it is early morning.";
    case 10..13: return "The sun is climbing towards its midday point.";
    case 14..17: return "The sun has passed its midday point, it is " +
                        "afternoon.";
    case 18..22: return "The sun is setting, it is late evening.";
    default:     return 0;
    }
}

public string
query_item_moon_phase()
{
    switch (EMP_D_TIME->query_day_of_month()) {
    case 0..2:   return "It is new.";
    case 3..6:   return "It is in the waxing crescent phase.";
    case 7..9:   return "It is in its first quarter.";
    case 10..13: return "It is in the waxing gibbous phase.";
    case 14..16: return "It is full.";
    case 17..20: return "It is in the waning gibbous phase.";
    case 21..23: return "It is in its last quarter.";
    case 24..27: return "It is in the waning crescent phase.";
    default:     return 0;
    }
}

public string
query_item_moon()
{
    string str;
    str = query_item_moon_phase();
    switch (EMP_D_TIME->query_hour_of_day()) {
    case 0..1: return "The moon is rising in the sky, and the night is " +
                      "still young. " + str;
    case 2:    return "The moon is at its highest point, it's the middle " +
                      "of the night. " + str;
    case 3..5: return "The moon is slowly descending, the night is getting " +
                      "old. " + str;
    default:   return 0;
    }
}

public string
query_item_stars()
{
    switch (EMP_D_TIME->is_day() * 2 +
            random(2)) {
    case 0:  return "You see Odin's Wain across the sky, where Thor rides " +
                    "his mighty chariot from time to time.";
    case 1:  return "You see Frigga's Spinning Wheel, consisting of three " +
                    "bright stars, one of them red.";
    default: return 0;
    }
}

public string
query_item_heaven()
{
    switch (EMP_D_TIME->is_day()) {
    case 1:  return query_item_sun();
    case 0:  return query_item_moon() + " " + query_item_stars();
    default: return 0;
    }
}

public varargs mixed
query_item(string arg)
{
    if (query_property("indoors")) {
        return ::query_item(arg);
    }
    switch (arg) {
    case "heaven":
    case "sky":     return query_item_heaven();
    case "moon":    return query_item_moon();
    case "star":
    case "stars":   return query_item_stars();
    case "sun":     return query_item_sun();
    default:        return ::query_item(arg);
    }
}

public void
set_day_long(string val)
{
    _day_long = val;
}

public string
query_day_long()
{
    return _day_long;
}

public void
set_night_long(string val)
{
    _night_long = val;
}

public string
query_night_long()
{
    return _night_long;
}

public void
set_area_long(string val)
{
    _area_long = val;
}

public string
query_area_long()
{
    return _area_long;
}

public void
set_long(mixed val)
{
    if (functionp(val)) {
        ::set_long(val);
    } else {
        set_day_long(val);
        set_night_long(val);
    }
}

public void
on_long(string arg, int nonl)
{
    object ply;
    int width, ansi;
    if (!objectp(ply = this_player())) {
        return;
    }
    ansi = (string)ply->query_property("TERM") == "ansi";
    width = ply->query_width();
    tell_ansi(ply, format_long(query_desc_long(), ansi, width));
}

public string
query_desc_nearby(int range, object ply)
{
    string *nearby_keys, *out;
    mapping nearby_map, colour;
    object *hunter, *prey;
    int i, len;
    if (!mapp(nearby_map = query_livings_nearby(range)) ||
	(len = sizeof(nearby_keys = keys(nearby_map))) == 0)
    {
	return 0;
    }
    if (!mapp(colour = ply->query_property("COLOURS"))) {
        colour = ([ ]);
    }
    hunter = filter_array(ply->query_fleed_from(), "can_see");
    prey   = filter_array(ply->query_pre_attackers(), "can_see");
    out    = ({ });
    for (i = 0; i < len; ++i) {
        object *lst;
	string key;
	if (!stringp(key = nearby_keys[i])) {
	    continue;
	}
        if (sizeof(lst = nearby_map[key] & hunter) > 0) {
            out += ({ colour["hityou"] + make_list(lst->query_name()) +
                      "%^END%^ looking for you to the " +
                      colour["exits"] + key + "%^END%^" });
        }
        if (sizeof(lst = nearby_map[key] & prey) > 0) {
            out += ({ colour["youhit"] + make_list(lst->query_name()) +
                      "%^END%^ running from you to the " +
                      colour["exits"] + key + "%^END%^" });
        }
    }
    return sizeof(out) > 0 ? "You see " + make_list(out) + "." : 0;
}

static int
can_see(object foe)
{
    if (!objectp(foe) ||
        foe->query_invis() ||
	!stringp(foe->short()) ||
        !stringp(foe->query_name()))
    {
        return 0;
    }
    return 1;
}

public varargs mixed
long(string arg)
{
    mixed ret;
    object ply;
    string str;
    ret = ::long(arg);
    if (!stringp(arg) &&
	objectp(ply = this_player()) && !ply->test_dark(1) &&
	stringp(str = query_desc_nearby(5, ply)))
    {
	write(str + "\n");
    }
    return ret;
}
