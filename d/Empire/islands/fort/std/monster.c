#include "/d/Empire/islands/fort.h"

inherit EMP_I_MONSTER;

static void init_dangerlevel(int old_val, int new_val);

static void
create()
{
    ::create();
    set_aggressive(1);
    set_log_file("fort");
    add_property("guardian");
}

public nomask void
set_dangerlevel(int val)
{
    int old_val, new_val;
    old_val = query_property("dangerlevel");
    new_val = max(0, min(100, val));

    add_property("dangerlevel", new_val);
    init_dangerlevel(old_val, new_val);
}

public nomask int
query_dangerlevel()
{
    return query_property("dangerlevel");
}
