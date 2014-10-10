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
        obj->add_property("wood");
    }
    switch (random(16)) {
    case  0: return "balsam fir";   
    case  1: return "cedar";        
    case  2: return "cypress";      
    case  3: return "hemlock";      
    case  4: return "larch";        
    case  5: return "noble fir";    
    case  6: return "red pine";     
    case  7: return "redwood";      
    case  8: return "silver fir";   
    case  9: return "spruce";       
    case 10: return "sugar pine";   
    case 11: return "white cedar";  
    case 12: return "white pine";   
    case 13: return "yellow cedar"; 
    case 14: return "yellow pine";  
    case 15: return "yew"; 
    default: error("Index out of bounds.");
    }
}

public varargs string 
random_noble(object obj) 
{
    if (objectp(obj)) {
        obj->add_property("wood");
    }
    switch (random(87)) {
    case  0: return "applewood"; 
    case  1: return "balsa"; 
    case  2: return "balsam poplar"; 
    case  3: return "bamboo"; 
    case  4: return "basswood"; 
    case  5: return "bigtooth aspen"; 
    case  6: return "black alder"; 
    case  7: return "black ash"; 
    case  8: return "black cherry"; 
    case  9: return "black ebony"; 
    case 10: return "black locust"; 
    case 11: return "black maple"; 
    case 12: return "black oak"; 
    case 13: return "black poplar"; 
    case 14: return "black walnut"; 
    case 15: return "black willow"; 
    case 16: return "blackwood"; 
    case 17: return "bloodwood"; 
    case 18: return "blue ash"; 
    case 19: return "boxwood"; 
    case 20: return "buckeye"; 
    case 21: return "bur oak"; 
    case 22: return "chestnut"; 
    case 23: return "chestnut oak"; 
    case 24: return "coachwood"; 
    case 25: return "coconut timber"; 
    case 26: return "common ash"; 
    case 27: return "corkwood"; 
    case 28: return "cricket-bat willow"; 
    case 29: return "dogwood"; 
    case 30: return "eastern cottonwood"; 
    case 31: return "garbon ebony"; 
    case 32: return "gray birch"; 
    case 33: return "green ash"; 
    case 34: return "honey locust"; 
    case 35: return "hornbeam"; 
    case 36: return "ironbark"; 
    case 37: return "kingwood"; 
    case 38: return "lacewood"; 
    case 39: return "laural oak"; 
    case 40: return "mahogany"; 
    case 41: return "manitoba maple"; 
    case 42: return "marble-wood"; 
    case 43: return "marblewood"; 
    case 44: return "mockernut hickory"; 
    case 45: return "pignut hickory"; 
    case 46: return "plains cottonwood"; 
    case 47: return "post oak"; 
    case 48: return "quaking aspen"; 
    case 49: return "red alder"; 
    case 50: return "red cedar"; 
    case 51: return "red cherry"; 
    case 52: return "red elm"; 
    case 53: return "red maple"; 
    case 54: return "red oak"; 
    case 55: return "river birch"; 
    case 56: return "rock elm"; 
    case 57: return "rosewood"; 
    case 58: return "sandalwood"; 
    case 59: return "satinwood"; 
    case 60: return "shagbark hickory"; 
    case 61: return "shellbark hickory"; 
    case 62: return "silver birch"; 
    case 63: return "silver maple"; 
    case 64: return "snakewood"; 
    case 65: return "southern live oak"; 
    case 66: return "sugar maple"; 
    case 67: return "swamp chestnut oak"; 
    case 68: return "swamp cottonwood"; 
    case 69: return "swamp white oak"; 
    case 70: return "sycamore maple"; 
    case 71: return "teak"; 
    case 72: return "walnut"; 
    case 73: return "water oak"; 
    case 74: return "wenge"; 
    case 75: return "white ash"; 
    case 76: return "white basswood"; 
    case 77: return "white birch"; 
    case 78: return "white oak"; 
    case 79: return "white willow"; 
    case 80: return "wild cherry"; 
    case 81: return "willow oak"; 
    case 82: return "wych elm"; 
    case 83: return "yellow birch"; 
    case 84: return "yellow buckeye"; 
    case 85: return "yellow locust"; 
    case 86: return "yellow poplar"; 
    case 87: return "zebrawood"; 
    default: error("Index out of bounds.");
    }
}

public varargs string 
random_wood(int quality, object obj) 
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
    case  0..19: return "about to break";
    case 20..39: return "is starting to come apart";
    case 40..59: return "has quite a few cuts";
    case 60..79: return "has a few cuts";
    case 80..99: return "has a few scratches";
    default:     return 0;
    }
}
