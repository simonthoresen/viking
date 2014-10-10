#include "/d/Empire/islands/ruins.h"

inherit RUN_I_ROOM;

static void
create()
{
    ::create();
    add_exit(EMP_DIR_VAR_ISLANDS + "reikland/63/44", "south");
}
