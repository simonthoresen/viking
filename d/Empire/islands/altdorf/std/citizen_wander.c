#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN_BASE;

private int _last_time;

private void
schedule_goal() 
{
    clear_goal();
    set_wandering_hook(store_fp("random_goal"));
}

static void
create() 
{
    ::create();
    _last_time = 0;

    schedule_goal();
    add_hook("__wander_done", store_fp("exclaim_goal"));
    add_hook("__wander_fail", store_fp("complain_lost"));
    add_response(({ "going" }), store_fp("say_goal"));
}

private int *
find_specials(string *map) 
{
    int row_idx, row_len;
    int col_idx, col_len;
    int *ret;
    if (!arrayp(map)) {
	return 0;
    }
    ret = ({ });
    for (row_idx = 0, row_len = sizeof(map);
	 row_idx < row_len; ++row_idx)
    {
	string row;
	for (col_idx = 0, col_len = strlen(row = map[row_idx]);
	     col_idx < col_len; ++col_idx)
	{
	    if (row[col_idx] >= 'A' &&
		row[col_idx] <= 'Z')
	    {
		ret += ({ to_pos(row_idx, col_idx) });
	    }
	}
    }
    return ret;
}

static string
random_goal() 
{
    object env;
    string island, *arr;
    int *opts, len, pos;
    if (!objectp(env = environment()) || !env->is_road() ||
        !stringp(island = env->query_island()))
    {
        load_chat(5, ({ "*sob", "*sulk", "*say I am lost." }));
        set_wandering_chance(0);
        return "sigh";
    }
    if (!arrayp(opts = find_specials(island->query_map())) ||
	(len = sizeof(opts)) == 0)
    {
        load_chat(5, ({ "*bored", "*twiddle", "*say I have nowhere to go." }));
        set_wandering_chance(0);
        return "ponder";
    }
    pos = opts[random(sizeof(opts))];
    if (!set_goal(to_row(pos), to_col(pos))) {
        return "say How do I get to the " + 
               island->query_name_at(to_row(pos), to_col(pos)) + "?";
    }
    return "say I am going to visit the " +
	   island->query_name_at(to_row(pos), to_col(pos)) + "!";
}

static void
exclaim_goal() 
{
    schedule_goal();
    set_wandering_route(({ "say I am exactly where I want to be!" }));
}

static void
complain_lost(mixed cmd) 
{
    schedule_goal();
    if (stringp(cmd)) {
        command("say I was certain that I could go " + cmd + " here..");
    } else {
	command("scratch");
    }
}

static string
say_goal() 
{
    string str;
    if (!stringp(str = query_goal_name())) {
	return "I am not going anywhere.";
    } else {
	return "I am on my way to the " + str + ".";
    }
}
