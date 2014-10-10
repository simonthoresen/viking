#include "/d/Artifact/artifact.h"

inherit EMP_I_COMMAND;

private string
format_progress(object ply, string name)
{
    if (ART_D_QUEST->is_unlocked(ply, name)) {
        return "[ %^L_GREEN%^DONE%^END%^ ]";
    }
    if (ART_D_QUEST->is_blocked(name)) {
        return "[  %^L_RED%^NA%^END%^  ]";
    }
    return sprintf("[ %2d %% ]", ART_D_QUEST->query_progress(ply, name));
}

private string *
create_list(object ply)
{
    string *arr, *ret;
    int i, len;
    ret = ({ });
    arr = sort_array(ART_D_QUEST->query_items(), "cmp_quest");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        if (!ART_D_QUEST->can_see(ply, arr[i])) {
            continue;
        }
        ret += ({ sprintf("%-30s %s",
                          ART_D_QUEST->query_title(arr[i]),
                          format_progress(ply, arr[i])) });
    }
    return ret;
}

static int
cmp_quest(string lhs, string rhs)
{
    return strcmp(ART_D_QUEST->query_title(lhs),
                  ART_D_QUEST->query_title(rhs));
}

static int
main(string arg)
{
    object ply;
    ply = this_player();
    if (wizardp(ply) &&
        stringp(arg) &&
        !objectp(ply = find_player(arg)))
    {
        return notify_fail("No such player.");
    }
    EMP_D_LIST->write_ansi(
            "Quest name                     Status  ",
            create_list(ply), 1);
    return 1;
}

public string
short_help()
{
    return "Show all quests.";
}
