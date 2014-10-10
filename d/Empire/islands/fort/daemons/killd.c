#include "/d/Empire/islands/fort.h"

inherit EMP_I_DAEMON;

private int _num_kills;

static void
create()
{
    ::create();
    _num_kills = 0;
}

public void
add_num_kills(int val)
{
    _num_kills += val;
}

public int
query_num_kills()
{
    return _num_kills;
}
