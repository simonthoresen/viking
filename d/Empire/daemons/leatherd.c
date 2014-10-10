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
        obj->add_property("leather");
    }
    switch (random(7)) {
    case 0:  return "cattle skin"; 
    case 1:  return "deer skin";   
    case 2:  return "dog skin";    
    case 3:  return "elk skin";    
    case 4:  return "goat skin";   
    case 5:  return "lamb skin";   
    case 6:  return "pig skin";    
    default: error("Index out of bounds.");
    }
}

public varargs string
random_noble(object obj) 
{
    if (objectp(obj)) {
        obj->add_property("leather");
    }
    switch (random(7)) {
    case 0:  return "alligator skin"; 
    case 1:  return "buffalo skin";   
    case 2:  return "crocodile skin"; 
    case 3:  return "kangaroo skin";  
    case 4:  return "snake skin";     
    case 5:  return "sting ray skin"; 
    case 6:  return "yak skin";       
    default: error("Index out of bounds.");
    }
}

public varargs string
random_leather(int quality, object obj) 
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
