#include "/d/Empire/empire.h"

static void create() {
    /* empty */
}

public int can_float(object obj) {
    if (!objectp(obj)) {
        return 0;
    }
    if (obj->query_property("container") ||
        obj->query_property("corpse") ||
        obj->query_property("drink"))
    {
        return 1;
    }
    if (obj->query_property("metal") || 
        obj->query_weight() > 0) 
    {
        return 0;
    }
    return 1;
}

public int can_fly(object ply) {
    if (!objectp(ply)) {
        return 0;
    }
    if (ply->id("bird") ||
        ply->query_property("flying") ||
        ply->query_tmp_prop("flying"))
    {
        return 1;
    }
    return 0;
}

public int can_swim(object ply) {
    if (!objectp(ply)) {
        return 0;
    }
    if (ply->id("fish") || 
        ply->query_skill("swimming") > random(100)) 
    {
        return 1;
    }
    return 1;
}
