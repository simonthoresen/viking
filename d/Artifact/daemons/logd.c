#include "/d/Artifact/artifact.h"

inherit EMP_I_LOGD;

static void
create()
{
    ::create();
    set_log_dir(ART_DIR_LOG);
    set_save_file(ART_DIR_VAR + "logd");
}
