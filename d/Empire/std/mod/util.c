#include "/d/Empire/empire.h"

inherit ansi   EMP_I_ANSI;
inherit array  EMP_I_ARRAY;
inherit call   EMP_I_CALL_OUT;
inherit can    EMP_I_CAN;
inherit dest   EMP_I_DESTROY;
inherit file   EMP_I_FILE;
inherit math   EMP_I_MATH;
inherit notify EMP_I_NOTIFY_FAIL;
inherit pos    EMP_I_POS;
inherit str    EMP_I_STRING;
inherit time   EMP_I_TIME;

static void
create()
{
    ansi::create();
    array::create();
    call::create();
    can::create();
    dest::create();
    file::create();
    math::create();
    notify::create();
    pos::create();
    str::create();
    time::create();
}
