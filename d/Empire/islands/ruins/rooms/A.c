#include "/d/Empire/islands/ruins.h"

inherit RUN_I_ROOM;

static void
create()
{
    ::create();
    add_reset_object("statue", RUN_DIR_OBJ + "aegir_statue");
}
