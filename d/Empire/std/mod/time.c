#include "/d/Empire/empire.h"

static void
create() 
{
    /* empty */
}

public int *
parse_time(string str) 
{
    int day, month;
    switch (str[0..2]) {
    case "Mon": day = 1; break;
    case "Tue": day = 2; break;
    case "Wed": day = 3; break;
    case "Thu": day = 4; break;
    case "Fri": day = 5; break;
    case "Sat": day = 6; break;
    case "Sun": day = 7; break;
    default:    error("Illegal day in time string '" + str + "'.");
    }
    switch (str[4..6]) {
    case "Jan": month = 1;  break;
    case "Feb": month = 2;  break; 
    case "Mar": month = 3;  break; 
    case "Apr": month = 4;  break; 
    case "May": month = 5;  break;
    case "Jun": month = 6;  break;
    case "Jul": month = 7;  break;
    case "Aug": month = 8;  break;
    case "Sep": month = 9;  break; 
    case "Oct": month = 10; break; 
    case "Nov": month = 11; break; 
    case "Dec": month = 12; break;
    default:    error("Illegal month in time string '" + str + "'.");
    }
    return ({ 
        to_int(str[20..23]),
        month,
        to_int(str[str[8] != ' ' ? 8 : 9..9]),
        day,
        to_int(str[11..12]),
        to_int(str[14..15]),
        to_int(str[17..18])
    });
}
