#include <mudlib.h>

inherit CMD_MODULE;

static int
main(string arg) 
{
    this_player()->heal_self(666);
    write("Ok.\n");
    return 1;
}
