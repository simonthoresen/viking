#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    if (wizardp(this_player())) {
        return 0;
    }
    write("You can not do that.\n");
    return 1;
}

public string
short_help()
{
    return "Do nothing.";
}
