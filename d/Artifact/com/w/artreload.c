#include "/d/Artifact/artifact.h"

inherit base CMD_MODULE;
inherit file EMP_I_FILE;

private string _this;

static void
create()
{
    base::create();
    file::create();
    _this = source_file_name() + ".c";
}

static int
main(string arg) 
{
    updir(ART_DIR, 1, store_fp("ignore_self"));
    ART_D_SLIVER->__bootstrap();
    write("Ok.\n");
    return 1;
}

static int
ignore_self(string file)
{
    if (file_size(file) == -2) {
        EMP_DEBUG(this_player(), file);
    }
    return file == _this;
}
