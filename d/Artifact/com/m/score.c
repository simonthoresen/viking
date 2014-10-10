#include "/d/Artifact/artifact.h"

inherit "/com/g/score";

private string
format_slots(object ply)
{
    mapping dat;
    string *arr, *ret;
    object obj;
    int i, len;
    if (!objectp(obj = ART_C_WEAPON->get_instance(ply)) ||
        !mapp(dat = obj->query_slots()) ||
        (len = sizeof(arr = keys(dat))) == 0)
    {
        return "none";
    }
    ret = ({ });
    for (i = 0; i < len; ++i) {
        int val;
        if ((val = dat[arr[i]]) != 0) {
            ret += ({ val + " " + arr[i] + (val > 1 ? "s" : "") });
        }
    }
    if (sizeof(ret) == 0) {
        return "none";
    }
    return make_list(ret);
}

static int
main(string arg)
{
    int ret;
    object ply;
    if ((ret = ::main("-l")) != 0 &&
        objectp(ply = this_player()) &&
        !ply->query_dead())
    {
        printf("Free slots : %s\n%'-'79s\n", format_slots(ply), "");
    }
    return ret;
}
