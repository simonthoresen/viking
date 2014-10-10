#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg) 
{
    object ply;
    string item, title;
    ply = this_player();
    if (ply->query_level() < ETERNAL_FIRST) {
        write("You need to be at least level " + ETERNAL_FIRST + 
              " to set your title.\n");
        return 1;
    }
    if (!stringp(arg)) {
        write("You are '" + ply->query_title() + "'.\n");
        return 1;
    }
    if (arg == "-c") {
        return 0; // fall through
    }
    if (sscanf(arg, "the %s", item)) {
        arg = item;
    }
    if (!stringp(item = ART_D_QUEST->query_item_by_title(arg)) ||
        !ART_D_QUEST->is_unlocked(ply, item))
    {
        write("You can only use unlocked quest names as title.\n");
        return 1;
    }
    if (!stringp(title = ART_D_QUEST->query_title(item))) {
        write("You fail.\n");
        return 1;
    }
    ply->set_title(title = "the " + title, 1);
    write("You are now '" + capitalize(ply->query_real_name()) + 
          " " + title + "'.\n");
    return 1;
}

public string
short_help() 
{
    return "Change your title.";
}
