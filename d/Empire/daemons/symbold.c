#include "/d/Empire/empire.h"

inherit I_DAEMON;

public string 
random_symbol() 
{
    switch (random(30)) {
    case  0: return "ankh";
    case  1: return "celtic cross";
    case  2: return "crescent";
    case  3: return "cross and crown";
    case  4: return "cross and flame";
    case  5: return "cross of sacrifice";
    case  6: return "cross";
    case  7: return "crucifix";
    case  8: return "dragon";
    case  9: return "eye of god";
    case 10: return "eye of providence";
    case 11: return "flaming chalice";
    case 12: return "fleur-de-lis";
    case 13: return "flower of life";
    case 14: return "hammer and sickle";
    case 15: return "high cross";
    case 16: return "maltese cross";
    case 17: return "papal cross";
    case 18: return "pentacle";
    case 19: return "pentagram";
    case 20: return "rose";
    case 21: return "skull and crossbones";
    case 22: return "skull";
    case 23: return "star and crescent";
    case 24: return "star";
    case 25: return "sun cross";
    case 26: return "torch";
    case 27: return "tree of life";
    case 28: return "tripe spiral";
    case 29: return "tudor rose";
    default: error("Index out of bounds.");
    }
}
