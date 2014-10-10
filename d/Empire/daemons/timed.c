#include "/d/Empire/empire.h"

inherit EMP_I_DAEMON;

private int _year;
private int _month_of_year;
private int _day_of_month;
private int _day_of_week;
private int _hour_of_day;
private int _minute_of_hour;
private int _second_of_minute;

static void
sample_time()
{
    int *arr;
    arr = parse_time(ctime(time()));
    _year             = arr[0];
    _month_of_year    = arr[1];
    _day_of_month     = arr[2];
    _day_of_week      = arr[3];
    _hour_of_day      = arr[4];
    _minute_of_hour   = arr[5];
    _second_of_minute = arr[6];
}

static void
create()
{
    ::create();
    sample_time();
    set_heart_beat(1);
}

public void
heart_beat()
{
    sample_time();
}

public int
query_day_of_month()
{
    return _day_of_month;
}

public int
query_day_of_week()
{
    return _day_of_week;
}

public int
query_hour_of_day()
{
    return _hour_of_day;
}

public int
query_minute_of_hour()
{
    return _minute_of_hour;
}

public int
query_month_of_year()
{
    return _month_of_year;
}

public int
query_second_of_minute()
{
    return _second_of_minute;
}

public int
query_year()
{
    return _year;
}

public int
query_season()
{
    switch (_month_of_year) {
    case 3..5:  return EMP_SEASON_SPRING;
    case 6..8:  return EMP_SEASON_SUMMER;
    case 9..11: return EMP_SEASON_AUTUMN;
    default:    return EMP_SEASON_WINTER;
    }
}

public int
query_weather()
{
    return (time() / 666) % 2;
}

public int
is_day()
{
    switch (_hour_of_day) {
    case 23:
    case 0..5:  return 0;
    case 6..22:
    default:    return 1;
    }
}

public int
is_night()
{
    return !is_day();
}

public int
is_morning()
{
    switch (_hour_of_day) {
    case 6..9: return 1;
    default:   return 0;
    }
}

public int
is_evening()
{
    switch (_hour_of_day) {
    case 18..22: return 1;
    default:     return 0;
    }
}

public string
query_day_name()
{
    switch (_day_of_week) {
    case 1:  return "Monday";
    case 2:  return "Tuesday";
    case 3:  return "Wednesday";
    case 4:  return "Thursday";
    case 5:  return "Friday";
    case 6:  return "Saturday";
    case 7:  return "Sunday";
    default: return 0;
    }
}

public string
query_month_name()
{
    switch (_month_of_year) {
    case 1:  return "January";
    case 2:  return "February";
    case 3:  return "March";
    case 4:  return "April";
    case 5:  return "May";
    case 6:  return "June";
    case 7:  return "July";
    case 8:  return "August";
    case 9:  return "September";
    case 10: return "October";
    case 11: return "November";
    case 12: return "December";
    default: return 0;
    }
}

public string
query_season_name()
{
    switch (query_season()) {
    case EMP_SEASON_SPRING: return "spring";
    case EMP_SEASON_SUMMER: return "summer";
    case EMP_SEASON_AUTUMN: return "autumn";
    case EMP_SEASON_WINTER: return "winter";
    default:                return 0;
    }
}

public string
query_stime()
{
    string str;
    int hour, minute;
    hour   = _hour_of_day;
    minute = _minute_of_hour;
    if (minute > 30) {
        ++hour;
    }
    switch (hour) {
    case 0:      str = "midnight"; break;
    case 12:     str = "noon"; break;
    case 1..11:  str = convert_number(hour); break;
    case 13..23: str = convert_number(hour - 12); break;
    default:     return 0;
    }
    switch (minute) {
    case 0:      return str + (hour == 0 || hour == 12 ? "" : " o'clock");
    case 1..29:  return convert_number(minute) + " past " + str;
    case 30:     return "half past " + str;
    case 31..59: return convert_number(60 - minute) + " to " + str;
    default:     return 0;
    }
}
