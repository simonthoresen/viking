#include "/d/Empire/empire.h"

inherit base I_WMONSTER;
inherit util EMP_I_UTIL;

private int _create_done;

static void
create()
{
    base::create();
    util::create();
    _create_done = 0;
    call_out("create_done", 0);
}

public void 
create_done()
{
    _create_done = 1;
}

public nomask int
is_create_done()
{
    return _create_done;
}
