#include "/d/Empire/empire.h"

static void
create()
{
    /* empty */
}

public nomask void
destroy_later()
{
    call_out("destroy", 0);
}
