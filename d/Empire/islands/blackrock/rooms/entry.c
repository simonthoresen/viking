#include "/d/Empire/islands/blackrock.h"

#define NUM_RECORDS   (5)

inherit I_ROOM;

private string _long_desc;
private int    _prev_change;

static void create() {
    ::create();
    _long_desc   = 0;
    _prev_change = 0;

    set_light(1);
    set_short("At the entrance to Blackrock depths");
    set_long(store_fp("my_long"));
    add_reset_object("merchant", BRD_DIR_OBJ + "merchant");
    add_hook("__reset", store_fp("check_files"));
    add_exit(R_VOID, "down", store_fp("try_exit"));
    add_exit(EMP_DIR_VAR_ISLANDS + "reikland/6/27", "out");
    add_property("no_wander");
}

static void check_files(int flag) {
    if (!BRD_ISLAND->has_room_files()) {
        BRD_ISLAND->try_recreate(30);
    }
}

private string create_table(string lhs_name, mixed lhs_scores, 
			    string rhs_name, mixed rhs_scores,
			    function fmt) 
{
    string hr, ret;
    int i, lhs_len, rhs_len;
    lhs_len = arrayp(lhs_scores) ? sizeof(lhs_scores) : 0;
    rhs_len = arrayp(rhs_scores) ? sizeof(rhs_scores) : 0;
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

static string fmt_score(int val) {
    return (string)val;
}

static string fmt_time(int val) {
    string ret;
    ret = ctime(val);
    return ret[4..strlen(ret) - 1];
}

private string create_long() {
    return sprintf("You are at the entrance to the caves of Blackrock " +
		   "mountain. You are free to climb down and pit yourself " +
		   "against the horrors of the deep.\n\n%s\n%s", 
                   create_table("Coin Count", 
                                BRD_D_SCORE->query_coin_count(),
                                "Solved Count",
                                BRD_D_SCORE->query_solve_count(),
				store_fp("fmt_score")),
                   create_table("Last Coin", 
                                BRD_D_SCORE->query_last_coin(),
                                "Last Solved",
                                BRD_D_SCORE->query_last_solve(),
                                store_fp("fmt_time")));
}

public void my_long() {
    int	next_change;
    next_change = BRD_D_SCORE->query_last_change();
    if (!stringp(_long_desc) || _prev_change != next_change) {
	_long_desc = create_long();
	_prev_change = next_change;
    }    
    write(_long_desc);
}

public int try_exit(string arg) {
    object obj;
    if (objectp(present(BRD_C_KEEPER))) {
        write("The caves are being reconstructed, try again later.\n");
	return 1;
    }
    if (!objectp(obj = BRD_ISLAND->load_entry())) {
        BRD_ISLAND->try_recreate();
        return 1;
    }
    this_player()->move_player("down", obj);
    return 1;
}
