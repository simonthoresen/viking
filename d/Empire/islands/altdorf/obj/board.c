#include "/d/Empire/islands/altdorf.h"

inherit I_ULTRA_BOARD;

static void
create() 
{
    ::create();
    set_name("empire board");
    add_id(({ "board", "empire board" }));
    set_short("a board nailed to the wall");
    set_headline("The Empire Board");
    set_notes_dir(EMP_DIR_VAR_BOARDS + "altdorf/");
    set_board_status("public");
    set_write_level(2);
}
