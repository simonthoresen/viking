#include "/d/Empire/empire.h"

inherit base CMD_MODULE;
inherit util EMP_I_UTIL;

static void
create()
{
    base::create();
    util::create();
}
