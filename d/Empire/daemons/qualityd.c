#include "/d/Empire/empire.h"

inherit I_DAEMON;

public string desc_quality(int quality, object obj) {
    string str, *arr;
    if (!objectp(obj)) {
        return 0;
    }
    arr = ({ });
    if (obj->query_property("cloth") && 
        stringp(str = EMP_D_CLOTH->desc_quality(quality))) 
    {
        arr += ({ "the cloth " + str });
    }
    if (obj->query_property("fur") && 
        stringp(str = EMP_D_FUR->desc_quality(quality))) 
    {
        arr += ({ "the fur " + str });
    }
    if (obj->query_property("leather") && 
        stringp(str = EMP_D_LEATHER->desc_quality(quality))) 
    {
        arr += ({ "the leather " + str });
    }
    if (obj->query_property("metal") && 
        stringp(str = EMP_D_METAL->desc_quality(quality))) 
    {
        arr += ({ "the metal " + str });
    }
    if (obj->query_property("wood") && 
        stringp(str = EMP_D_WOOD->desc_quality(quality))) 
    {
        arr += ({ "the wood " + str });
    }
    if (sizeof(arr) == 0) {
        return 0;
    }
    return capitalize(make_list(arr)) + ".";
}
