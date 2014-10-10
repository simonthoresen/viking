#include "/d/Empire/islands/fort.h"

inherit EMP_I_ROOM;

private string _wing;

static void
create()
{
    ::create();
    _wing = 0;
    add_property(({ "indoors", "no_telein" }));
}

public void
set_wing(string val)
{
    _wing = val;
}

public string
query_wing()
{
    return _wing;
}
