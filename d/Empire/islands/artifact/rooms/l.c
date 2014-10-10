#include "/d/Empire/islands/artifact.h"

inherit EMP_DIR_STD + "map_l";

static void
create()
{
    ::create();
    add_property("no_nothing");
}

static void
check_enter(object obj, object from)
{
    /* disable */
}

static void
check_burn(object ply)
{
    /* disable */
}
