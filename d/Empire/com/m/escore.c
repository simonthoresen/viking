#include <std.h>
#include "/d/Empire/islands/arena.h"

inherit base CMD_MODULE;
inherit util EMP_I_UTIL;

static void create() {
    base::create();
    util::create();
}

string format_time(int val) {
    string now, str;
    if (val == 0) {
	return "n/a";
    }
    str = ctime(val);
    now = ctime(time());
    if (str[ 4..10] != now[4..10] ||
        str[20..23] != now[20..23]) 
    {
        return str[4..10] + str[20..23];
    }
    return "Today " + str[11..18];
}

string format_title(string title, int len) {
    if (strlen(title) <= len) {
        return title;
    }
    return title[0..len - 1];
}

string format_progress(int val) {
    if (val < 0) {
	return "        ";
    } else if (val < 100) {
	return sprintf("[  %2d%% ]", val);
    } else {
	return "[ %^L_GREEN%^DONE%^END%^ ]";
    }
}

string format_column(string name, mapping lhs, mapping rhs) {
    if (!mapp(lhs)) {
        return sprintf("%-29s %s",
                       format_title(EMP_D_ACHIEVEMENT->query_title(name), 29),
                       format_progress(mapp(rhs) ? rhs[name] : -1));
    } else {
        return sprintf("%-20s %s %s",
                       format_title(EMP_D_ACHIEVEMENT->query_title(name), 20),
                       format_progress(lhs[name]),
                       format_progress(mapp(rhs) ? rhs[name] : -1));
    }
}

string format_achievements(object lhs, object rhs) {
    mapping lhs_dat, rhs_dat;
    string *arr, ret;
    int arr_len, row, num_rows;
    lhs_dat = objectp(lhs) ? EMP_D_ACHIEVEMENT->query_achievements(lhs) : 0;
    rhs_dat = objectp(rhs) ? EMP_D_ACHIEVEMENT->query_achievements(rhs) : 0;
    arr = sort_array((mapp(lhs_dat) ? keys(lhs_dat) : ({ })) | 
		     (mapp(rhs_dat) ? keys(rhs_dat) : ({ })), 
		     "sort_alpha_asc", FILTER_OB);
    arr_len = sizeof(arr);
    ret = "";
    for (row = 0, num_rows = arr_len / 2 + arr_len % 2;
         row < num_rows; ++row) 
    {
        ret += sprintf("%s | %s\n",
		       format_column(arr[row], lhs_dat, rhs_dat),
		       (row >= arr_len - num_rows) ? "" : 
		       format_column(arr[row + num_rows], lhs_dat, rhs_dat));
    }
    return ret;
}

int format_kill_chance(int k_rating, int v_rating) {
    return (int)(100.0 * EMP_D_ANARCHY->query_kill_chance(k_rating, v_rating));
}

string format_pos(int val) {
    if (val < 0) {
	return "??";
    }
    return (string)(val + 1);
}

int main(string arg) {
    object ply, you;
    string hrule;
    you = this_player();
    if (stringp(arg) && strlen(arg = getopts("l", arg)) > 0) {
        if (!objectp(ply = find_player(arg))) {
            return notify_fail("That player is not online.");
        }
    } else {
	ply = this_player();
    }
    write(hrule = sprintf("%'-'79s\n", ""));
    write(sprintf("Name         : %-23s | " +
                  "Rating       : %16d ( %2s )\n",
                  capitalize(ply->query_real_name()),
                  EMP_D_ANARCHY->query_rating(ply),
                  format_pos(EMP_D_ANARCHY->query_rating_pos(ply))));
    if (ply != you) {
	int p_val, y_val;
	p_val = EMP_D_ANARCHY->query_rating(ply);
	y_val = EMP_D_ANARCHY->query_rating(you);
	write(sprintf("%38s | You kill     : %16s ( %2d%%)\n", "",
		      "+" + EMP_D_ANARCHY->query_rating_change(y_val, p_val), 
		      format_kill_chance(y_val, p_val)));
	write(sprintf("%38s | Kills you    : %16s ( %2d%%)\n", "",
		      "-" + EMP_D_ANARCHY->query_rating_change(p_val, y_val),
		      format_kill_chance(p_val, y_val)));
    }
    write(hrule);
    write(sprintf("Kill count   : %16d ( %2s ) | " +
                  "Death count  : %16d ( %2s )\n" +
                  "Kill streak  : %16d ( %2s ) | " +
                  "Death streak : %16d ( %2s )\n" +
                  "Last kill    : %16s ( %2s ) | " +
                  "Last death   : %16s ( %2s )\n",
                  ARN_D_SCORE->query_kill_count(ply),
                  format_pos(ARN_D_SCORE->query_kill_count_pos(ply)),
                  ARN_D_SCORE->query_death_count(ply),
                  format_pos(ARN_D_SCORE->query_death_count_pos(ply)),
                  ARN_D_SCORE->query_kill_streak(ply),
                  format_pos(ARN_D_SCORE->query_kill_streak_pos(ply)),
                  ARN_D_SCORE->query_death_streak(ply),
                  format_pos(ARN_D_SCORE->query_death_streak_pos(ply)),
                  format_time(ARN_D_SCORE->query_last_kill(ply)),
                  format_pos(ARN_D_SCORE->query_last_kill_pos(ply)),
                  format_time(ARN_D_SCORE->query_last_death(ply)),
                  format_pos(ARN_D_SCORE->query_last_death_pos(ply))));
    write(hrule);
    if (opts['l']) {
	tell_ansi(you, format_achievements(ply != you ? ply : 0, you));
    } else {
	write(EMP_D_ACHIEVEMENT->query_num_unlocked(ply) + 
	      " achievements unlocked.\n");
    }
    write(hrule);
    return 1;
}

string short_help() {
    return "Prints the Empire score of a player.";
}
