#include "/d/Empire/empire.h"

inherit base I_DAEMON;
inherit util EMP_I_UTIL;

static void
create() 
{
    base::create();
    util::create();
}

public varargs string 
random_base(object obj) 
{
    string type, prop;
    prop = "metal";
    switch (random(14)) {
    case  0: type = "bell metal";                   break;
    case  1: type = "bone";                         break;
    case  2: type = "brass";                        break;
    case  3: type = "cast iron";                    break;
    case  4: type = "cobalt";                       break;
    case  5: type = "copper";                       break;
    case  6: type = "iron";                         break;
    case  7: type = "lead";                         break;
    case  8: type = "nickel silver";                break;
    case  9: type = "nickel";                       break;
    case 10: type = "stone";        prop = "stone"; break;
    case 11: type = "tin";                          break;
    case 12: type = "wood's metal";                 break;
    case 13: type = "wrought iron"; prop = "iron";  break;
    default: error("Index out of bounds.");
    }
    if (objectp(obj)) {
        obj->add_property(prop);
    }
    return type;
}

public varargs string 
random_noble(object obj) 
{
    string type;
    switch (random(6)) {
    case 0: type = "bronze";  break;
    case 1: type = "eog";     break;
    case 2: type = "gold";    break;
    case 3: type = "mithril"; break;
    case 4: type = "silver";  break;
    case 5: type = "steel";   break;
    default: error("Index out of bounds.");
    }
    if (objectp(obj)) {
        obj->add_property(type);
        obj->set_value(obj->query_value() * 2);
        if (type == "mithril") {
            obj->set_weight(1);
        }
    }
    return type;
}

public varargs string 
random_metal(int quality, object obj) 
{
    switch (max(0, min(99, quality))) {
    case  0..49: return random_base(obj);
    case 50..99: return random_noble(obj);
    default:     error("Index out of bounds.");
    }
}

public string 
desc_quality(int quality, object obj) 
{
    switch (quality / 2 + random(quality)) {
    case  0..19: return "is rusted and worn";
    case 20..39: return "is starting to rust";
    case 40..59: return "has quite a few dents";
    case 60..79: return "has a few dents";
    case 80..99: return "has a few scratches";
    default:     return 0;
    }
}
