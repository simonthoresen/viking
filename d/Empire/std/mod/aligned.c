#include "/d/Empire/empire.h"

public varargs int add_hook(string h_name, mixed hook, mixed args);
public string      query_name();

private int _min_align;
private int _max_align;

static void
create()
{
    _min_align = 0x80000000;
    _max_align = 0x7fffffff;
    add_hook("__bwear", store_fp("prevent_wear"));
    add_hook("__bwield", store_fp("prevent_wield"));
}

static nomask int
prevent_wear(int silent, object obj)
{
    object ply;
    if (!objectp(ply = environment())) {
        return 0;
    }
    if (ply->query_alignment() < _min_align) {
        tell_object(ply, "You are too evil to wear " + query_name() + ".\n");
        return 1;
    }
    if (ply->query_alignment() > _max_align) {
        tell_object(ply, "You are too good to wear " + query_name() + ".\n");
        return 1;
    }
    return 0;
}

static nomask int
prevent_wield(object obj, string hands)
{
    object ply;
    if (!objectp(ply = environment())) {
        return 0;
    }
    if (ply->query_alignment() < _min_align) {
        tell_object(ply, "You are too evil to wield " + query_name() + ".\n");
        return 1;
    }
    if (ply->query_alignment() > _max_align) {
        tell_object(ply, "You are too good to wield " + query_name() + ".\n");
        return 1;
    }
    return 0;
}

public void
set_min_align(int val)
{
    _min_align = val;
}

public int
query_min_align()
{
    return _min_align;
}

public void
set_max_align(int val)
{
    _max_align = val;
}

public int
query_max_align()
{
    return _max_align;
}
