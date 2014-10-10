#include "/d/Artifact/artifact.h"

inherit EMP_I_UNLOCKD;

static void
create()
{
    ::create();
    set_prefix("art_quest_");
    set_item_dir(ART_DIR_ETC_QUESTS);
    set_save_file(ART_DIR_VAR + "questd");
}

static void
notify_unlock(object ply, string item)
{
    string out, title, desc;
    out  = sprintf("[ %|75s ]\n", "QUEST UNLOCKED:");
    out += sprintf("[ %75s ]\n", "");
    out += sprintf("[ %|75s ]\n", title = query_title(item));
    if (stringp(desc = query_desc(item))) {
        string *arr;
        int i, len;
        out += sprintf("[ %75s ]\n", "");
        arr = explode(break_string(desc, 75), "\n");
        for (i = 0, len = sizeof(arr); i < len; ++i) {
            out += sprintf("[ %-75s ]\n", arr[i]);
        }
    }
    tell_object(ply, "\n" + out + "\n");
    ART_MASTER->broadcast(ply->query_name() + " unlocked the quest '" +
                          title + "'.");
    ART_LOG("quests", ply->query_real_name() + " unlocked '" + item + "'");
}
