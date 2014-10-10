#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private object _hound;
private string _limb;

static void 
create() 
{
    ::create();
    _hound = 0;
    _limb  = 0;

    set_no_corpse(1);
    add_hook("__die", store_fp("on_die"));
}

static void 
on_die(object corpse, object foe) 
{
    if (objectp(_hound)) {
        EMP_D_LIMB->cut_limb(_hound, _limb);
    }
}

public void
set_limb(string val) 
{
    _limb = val;
}

public string
query_limb() 
{
    return _limb;
}

public void
set_hound(object val) 
{
    _hound = val;
}

public object
query_hound() 
{
    return _hound;
}

public int
is_cerberus() 
{
    return 1;
}
