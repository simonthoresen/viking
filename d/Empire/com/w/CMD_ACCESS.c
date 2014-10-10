#include "/d/Empire/empire.h"

int query_access(object ply) {
    return objectp(ply) && wizardp(ply);
}

string describe() {
    return "empire_wiz"; 
}
