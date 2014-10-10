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
    if (objectp(obj)) {
        obj->add_property("fur");
    }
    switch (random(4)) {
    case 0:  return "bear fur";      
    case 1:  return "rabbit fur";    
    case 2:  return "sheepskin fur"; 
    case 3:  return "wolf fur";      
    default: error("Index out of bounds.");
    }
}

public varargs string
random_noble(object obj) 
{
    if (objectp(obj)) {
        obj->add_property("fur");
    }
    switch (random(3)) {
    case 0:  return "beaver fur"; 
    case 1:  return "fox fur";    
    case 2:  return "mink fur";   
    default: error("Index out of bounds.");
    }
}

public varargs string
random_fur(int quality, object obj) 
{
    switch (max(0, min(99, quality))) {
    case  0..49: return random_base(obj);
    case 50..99: return random_noble(obj);
    default:     error("Index out of bounds.");
    }
}

public string
desc_quality(int quality) 
{
    switch (quality / 2 + random(quality)) {
    case  0..19: return "is ragged and torn";
    case 20..39: return "is starting to come apart";
    case 40..59: return "has quite a few dents";
    case 60..79: return "has a few dents";
    case 80..99: return "has a few scratches";
    default:     return 0;
    }
}
