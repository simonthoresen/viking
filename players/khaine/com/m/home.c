#include <mudlib.h>

inherit CMD_MODULE;

static int
main(string arg) 
{
    this_player()->move_player("X", "/players/khaine/workroom");
    return 1;
}
