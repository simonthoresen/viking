#include "/d/Empire/empire.h"

inherit base I_DAEMON;
inherit util EMP_I_UTIL;

static void
create() 
{
    base::create();
    util::create();
}

private string
random_weave() 
{
    switch (random(3)) {
    case 0:  return "plain";
    case 1:  return "satin";
    case 2:  return "twill";
    default: error("Index out of bounds.");       
    }
}

public varargs string
random_base(object obj, int no_weave) 
{
    string pre;
    if (objectp(obj)) {
        obj->add_property("cloth");
    }
    pre = (no_weave || random(2) ? "" : random_weave() + " woven ");
    switch (random(8)) {
    case 0:  return pre + "catgut"; 
    case 1:  return pre + "cotton"; 
    case 2:  return pre + "flax";   
    case 3:  return pre + "hemp";   
    case 4:  return pre + "jute";   
    case 5:  return pre + "ramie";  
    case 6:  return pre + "sinew";  
    case 7:  return pre + "sisal";  
    default: error("Index out of bounds.");
    }
}

public varargs string
random_noble(object obj, int no_weave) 
{
    string pre;
    if (objectp(obj)) {
        obj->add_property("cloth");
    }
    pre = (no_weave || random(2) ? "" : random_weave() + " woven ");
    switch (random(5)) {
    case 0:  return pre + "angora";      
    case 1:  return pre + "cashmere";    
    case 2:  return pre + "mohair";      
    case 3:  return pre + "spider silk"; 
    case 4:  return pre + "wool";        
    default: error("Index out of bounds.");
    }
}

public varargs string
random_cloth(int quality, object obj, int no_weave) 
{
    switch (max(0, min(99, quality))) {
    case  0..49: return random_base(obj, no_weave);
    case 50..99: return random_noble(obj, no_weave);
    default:     error("Index out of bounds.");
    }
}

public string 
desc_quality(int quality, object obj) 
{
    switch (quality / 2 + random(quality)) {
    case  0..19: return "ragged and torn";
    case 20..39: return "starting to come apart";
    case 40..59: return "has quite a few tears";
    case 60..79: return "has a few tears";
    case 80..99: return "has a few rips";
    default:     return 0;
    }
}
