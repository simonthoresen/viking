#include "/d/Empire/empire.h"

inherit I_DAEMON;

public string 
random_gemstone() 
{
    switch (random(28)) {
    case  0: return "agate";
    case  1: return "alexandrite";
    case  2: return "amber";
    case  3: return "amethyst";
    case  4: return "aquamarine";
    case  5: return "chalcedony";
    case  6: return "citrine";
    case  7: return "coral";
    case  8: return "diamond";
    case  9: return "emerald";
    case 10: return "feldspar";
    case 11: return "garnet";
    case 12: return "ivory";
    case 13: return "jade";
    case 14: return "malachite";
    case 15: return "obsidian";
    case 16: return "olivine";
    case 17: return "onyx";
    case 18: return "opal";
    case 19: return "pearl";
    case 20: return "quartz";
    case 21: return "ruby";
    case 22: return "sapphire";
    case 23: return "spinel";
    case 24: return "tanzanite";
    case 25: return "tiger's eye";
    case 26: return "topaz";
    case 27: return "turquoise";
    default: error("Index out of bounds.");
    }
}
