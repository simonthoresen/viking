#include "/d/Empire/islands/fort.h"

inherit EMP_DIR_STD + "map_r";

static void
create()
{
    ::create();
    add_exit(EMP_DIR_VAR_ISLANDS + "reikland/37/8", "west");
}
