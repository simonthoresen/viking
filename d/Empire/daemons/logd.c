#include "/d/Empire/empire.h"

inherit EMP_I_LOGD;

static void
create()
{
    ::create();
    set_log_dir(EMP_DIR_LOG);
    set_save_file(EMP_DIR_VAR + "logd");
}
