#include "/d/Empire/empire.h"

inherit util EMP_I_UTIL;
inherit hook I_HOOK;
inherit base I_DAEMON;
inherit dest I_DESTROY;

static void
create() 
{
    base::create();
    util::create();
}

static void
heart_beat() 
{
    hook("__heart_beat", ({ }));
}

static void
reset(int flag) 
{
    base::reset(flag);
    hook("__reset", ({ flag }));
}

static void
on_destruct() 
{
    /* empty */
}

