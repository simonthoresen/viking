#include "/d/Empire/islands/artifact.h"

inherit EMP_DIR_STD + "map_d";

static void
create()
{
    ::create();
    add_property("no_nothing");
}

public void
living_heart_beat(object ply)
{
    // disable burn
}
