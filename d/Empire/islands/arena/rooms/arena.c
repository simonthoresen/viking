#include "/d/Empire/islands/arena.h"

#define NUM_RECORDS   5
#define ARENA_COST    2500

inherit I_ROOM;

string _long_desc;
int    _prev_change;

void create() {
    ::create();
    _long_desc   = 0;
    _prev_change = 0;

    set_light(1);
    set_short("At the underground arena");
    set_long(store_fp("on_long"));
    add_item(({ "arena" }), "You may enter to fight others. You need to be" +
             " at full health and mana, and you must pay the " + ARENA_COST +
             " coin fee.");
    add_property(({ "anarchy", "indoors", "underground", "no_fight" }));
    add_exit(ARN_R_INSIDE, "enter", store_fp("check_vitals"));
    add_exit(ARN_R_LOUNGE, "west");
    add_exit("/room/shop_adv_tunnel", "east");
    add_hook("__enter_inv", store_fp("revive_ghost"));
}

void revive_ghost(object ply, object from) {
    if (objectp(ply) && ply->query_dead()) {
	ply->remove_ghost();
    }
}

int check_vitals() {
    object ply;
    if (!objectp(ply = this_player())) {
	return 0;
    }
    if (ply->query_hp() < ply->query_max_hp() ||
	ply->query_sp() < ply->query_max_sp())
    {
	write("You need to be at full health and mana to enter.\n");
	return 1;
    }
    if (ply->query_money() < ARENA_COST) {
        write("You do not have enough money.\n");
        return 1;
    }
    write("You pay " + ARENA_COST + " gold to one of the guards.\n");
    say(ply->query_name() + " pays one of the guards some money.\n");
    ply->add_money(-ARENA_COST);
    return 0;
}

varargs string create_table(string lhs_name, mixed lhs_scores, 
			    string rhs_name, mixed rhs_scores,
			    function fmt) 
{
    string hr, ret;
    int i, lhs_len, rhs_len;
    lhs_len = arrayp(lhs_scores) ? sizeof(lhs_scores) : 0;
    rhs_len = arrayp(rhs_scores) ? sizeof(rhs_scores) : 0;
    if (!functionp(fmt)) {
	fmt = store_fp("fmt_score");
    }
    hr = sprintf("%'" + (stringp(lhs_name) ? "-" : " ") + "'38s   " +
		 "%'" + (stringp(rhs_name) ? "-" : " ") + "'38s\n", "", "");
    ret = hr + sprintf("%-19s %18s   %-19s %18s\n", 
		       stringp(lhs_name) ? "Player" : "", 
		       stringp(lhs_name) ? lhs_name : "",
		       stringp(rhs_name) ? "Player" : "", 
		       stringp(rhs_name) ? rhs_name : "") + hr;
    for (i = 0; i < NUM_RECORDS && (i < lhs_len || i < rhs_len); ++i) {
        string lhs, rhs;
        if (i < lhs_len) {
            lhs = sprintf("%-13s %24s", capitalize(lhs_scores[i][0]),
			  call_fp(fmt, lhs_scores[i][1]));
        } else {
            lhs = "";
        } 
        if (i < rhs_len) {
            rhs = sprintf("%-13s %24s", capitalize(rhs_scores[i][0]),
                          call_fp(fmt, rhs_scores[i][1]));
        } else {
            rhs = "";
        } 
        ret += sprintf("%-38s   %-38s\n", lhs, rhs);
    }
    ret += hr;
    return ret;
}

string fmt_score(int val) {
    return (string)val;
}

string fmt_time(int val) {
    string ret;
    ret = ctime(val);
    return ret[4..strlen(ret) - 1];
}

string create_long() {
    return sprintf("You are at the underground arena. You can pay %d coins " +
                   "to enter and pit yourself against other players without " +
                   "the fear of death.\n\n%s\n%s\n%s\n%s\nUse the " +
                   "'escore' command to check your current score or " +
                   "'escore <name>' to see that of another. Use the '-l' " +
                   "option to include a list of achievements.", 
                   ARENA_COST,
                   create_table("Kill Count", 
                                ARN_D_SCORE->query_kill_counts(),
                                "Death Count",
                                ARN_D_SCORE->query_death_counts()),
                   create_table("Kill Streak",
                                ARN_D_SCORE->query_kill_streaks(),
                                "Death Streak", 
                                ARN_D_SCORE->query_death_streaks()),
                   create_table("Last Kill", 
                                ARN_D_SCORE->query_last_kills(),
                                "Last Death", 
                                ARN_D_SCORE->query_last_deaths(),
                                store_fp("fmt_time")),
                   create_table("Multi Kill", 
                                ARN_D_SCORE->query_multi_kills()));
}

void on_long(string arg, int nonl) {
    int	next_change;
    next_change = ARN_D_SCORE->query_last_change();
    if (!stringp(_long_desc) || _prev_change != next_change) {
	_long_desc = create_long();
	_prev_change = next_change;
    }    
    write(_long_desc);
}
