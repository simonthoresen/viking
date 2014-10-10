#include "/d/Empire/empire.h"

inherit base I_OBJECT;
inherit util EMP_I_UTIL;

static void
create() 
{
    base::create();
    util::create();
}
