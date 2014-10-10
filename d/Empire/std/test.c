#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

static void
create()
{
    ::create();
    set_name("test");
    set_hp(10000);
    set_scary(1);
}
