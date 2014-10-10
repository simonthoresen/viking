#include "/d/Artifact/artifact.h"

inherit I_ULTRA_BOARD;

static void
create()
{
    ::create();
    set_name("board");
    set_short("a bulletin board");
    set_headline("The Artifact Board");
    set_notes_dir(ART_DIR_VAR + "board/");
    set_board_status("public");
    add_id("bulletin board");
}
