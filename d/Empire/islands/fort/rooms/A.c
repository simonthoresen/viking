#include "/d/Empire/islands/fort.h"

inherit FOR_I_ENTRY;

static void
create()
{
    ::create();
    set_gated_exit("south");
}
