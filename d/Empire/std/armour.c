#include "/d/Empire/empire.h"

inherit base I_ARMOUR;
inherit util EMP_I_UTIL;

static void
create() 
{
    base::create();
    util::create();
}

public int 
query_weight() 
{
    int val;
    val = ::query_weight();
    if (val <= 0) {
        return 1;
    }
    if (!query_property("mithril")) {
        return val;
    }
    return (int)ceil((float)val / 2.0);
}

public int
drop(int silent) 
{
    if (query_verb() == "toss") {
        return CAN_DROP;
    }
    return ::drop(silent);
}
