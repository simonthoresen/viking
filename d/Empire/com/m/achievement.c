#include "/d/Empire/empire.h"

inherit CMD_MODULE;

string format_progress(object ply, string name) {
    int val;
    val = EMP_D_ACHIEVEMENT->query_achievement(ply, name);
    if (val < 0) {
        return "        ";
    } else if (val < 100) {
        return sprintf("[ %2d %% ]", val);
    } else {
        return "[ %^L_GREEN%^DONE%^END%^ ]";
    }
}

string format_time(int val) {
    string str;
    str = ctime(val);
    return str[4..10] + str[20..23];
}

string format_first(string name) {
    mixed val;
    if (!arrayp(val = EMP_D_ACHIEVEMENT->query_first(name))) {
        return "n/a";
    }
    return sprintf("%s by %s", format_time(val[1]), capitalize(val[0]));
}

void list_achievements(object ply) {
    string *arr, hrule;
    int i, len, width;
    width = ply->query_width();
    ply->set_width(666);

    write(hrule = sprintf("%'-'79s\n", ""));
    write(sprintf("%-38s   %s   %s\n", "Achievement",
                  "Progress", "First Unlock"));
    write(hrule);
    arr = get_files(EMP_DIR_ETC_ACHIEVEMENTS);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        string name;
        name = arr[i];
        write(sprintf("%-38s   %s   %s\n",
                      EMP_D_ACHIEVEMENT->query_title(name),
                      format_progress(ply, name),
                      format_first(name)));
    }
    write(hrule);
          
    ply->set_width(width);
}

int main(string arg) {
    object ply;
    string desc;
    int val;
    if (!objectp(ply = this_player())) {
	return 0;
    }
    if (!stringp(arg)) {
        list_achievements(ply);
        return 1;
    }
    arg = lower_case(arg);
    arg = replace_string(arg, " ", "_");
    if (!stringp(desc = EMP_D_ACHIEVEMENT->query_desc(arg))) {
	return notify_fail("No description available.");
    }
    write(desc + "\n");
    val = EMP_D_ACHIEVEMENT->query_achievement(ply, arg);
    if (val < 100) {
        write("Progress: " + val + "%\n");
    } else if (val >= 100) {
        write("Progress: %^L_GREEN%^UNLOCKED%^END%^\n");
    }
    return 1;
}

string short_help() {
    return "Prints the description of an achievement.";
}
