#include "/d/Empire/islands/reikland.h"

inherit EMP_DIR_STD + "map_p";

static void
create()
{
    ::create();
    add_exit("/d/Empire/var/islands/altdorf/26/0", "altdorf");
}
