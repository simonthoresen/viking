#include "/d/Empire/islands/reikland.h"

inherit EMP_DIR_STD + "map_f";

static void
create()
{
    ::create();
    set_long("A fort is being constructed here.");
    //add_exit("/d/Empire/var/islands/fort/22/0", "fort");
}
