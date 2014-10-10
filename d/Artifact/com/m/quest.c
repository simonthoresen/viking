
#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

private string
format_progress(object ply, string name) 
{
    if (ART_D_QUEST->is_blocked(name)) {
        return "[  %^L_RED%^NA%^END%^  ]";
    }
    if (!ART_D_QUEST->can_see(ply, name)) {
        return "[%^L_YELLOW%^HIDDEN%^END%^]";
    }
    if (ART_D_QUEST->is_unlocked(ply, name)) {
        return "[ %^L_GREEN%^DONE%^END%^ ]";
    }
    return sprintf("[ %2d %% ]", ART_D_QUEST->query_progress(ply, name));
}

private string
format_group(string item) 
{
    string str;
    if (!stringp(str = ART_D_QUEST->query_group_of(item))) {
        return "";
    }
    return ", in group " + str;
}

private string
format_title(object ply, string item) 
{
    string str;
    str = format_progress(ply, item) + " "  +
          ART_D_QUEST->query_title(item) +
          format_group(item);
    if (ART_D_QUEST->is_unique(item)) {
        str += " (unique)";
    }
    return str + "\n";
}

private string
format_desc(object ply, string item) 
{
    string str;
    if (!stringp(str = ART_D_QUEST->query_desc(item))) {
        return "";
    }
    if (ART_D_QUEST->is_unique(item)) {
        string name;
        if (stringp(name = ART_D_QUEST->query_first_name(item))) {
            str += " This quest is no longer available to unlock, since it" +
                   " has already been unlocked by " + capitalize(name) + ".";
        } else {
            str += " This quest is unique, meaning there can only be one" +
                   " player that unlocks it. Hurry up and be that player!";
        }
    } 
    return str + "\n";
}

private string
format_first(object ply, string item) 
{
    string str;
    if (!stringp(str = ART_D_QUEST->query_first_name(item))) {
        return "";
    } 
    return "\nIt was first unlocked by " + capitalize(str) + " on " + 
           ctime(ART_D_QUEST->query_first_time(item)) + ".\n";

}

static string
format_composite(object ply, string item) 
{
    string str, *arr;
    int i, len;
    if (!arrayp(arr = ART_D_QUEST->query_locked_by(item))) {
        return "";
    }
    str = "\nThis quest is unlocked by completing:\n";
    arr = sort_array(arr, "cmp_quest");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        str += sprintf("%s %s\n", 
                       format_progress(ply, arr[i]),
                       ART_D_QUEST->query_title(arr[i]));
    }
    return str;
}

static int
main(string arg)
{
    object ply;
    string item;
    if (!stringp(arg)) {
	return notify_fail("Show info on what quest?");
    }
    notify_fail("No such quest.");
    if (!stringp(item = ART_D_QUEST->query_item_by_title(arg))) {
        return 0;
    }
    if (!ART_D_QUEST->can_see(ply = this_player(), item) && !wizardp(ply)) {
        return 0;
    }
    write(format_title(ply, item) +
          format_desc(ply, item) + 
          format_composite(ply, item) +
          format_first(ply, item));
    return 1;
}

public string
short_help()
{
    return "Show information about a quest.";
}
