#include <levels.h>
#include "/d/Empire/islands/arena.h"

#define P_KILL_COUNT      ("arn_kill_count")
#define P_KILL_STREAK     ("arn_kill_streak")
#define P_KILL_LAST       ("arn_kill_last")
#define P_KILL_MULTI      ("arn_kill_multi")
#define P_DEATH_COUNT     ("arn_death_count")
#define P_DEATH_STREAK    ("arn_death_streak")
#define P_DEATH_LAST      ("arn_death_last")

#define KILL_MULTI_TIME   30
#define NUM_RECORDS       10

inherit I_DAEMON;

mixed _kill_count;
mixed _kill_streak;
mixed _kill_last;
mixed _kill_multi;
mixed _death_count;
mixed _death_streak;
mixed _death_last;
int   _last_change;

void create() {
    ::create();
    _kill_count   = 0;
    _kill_streak  = 0;
    _kill_last    = 0;
    _kill_multi   = 0;
    _death_count  = 0;
    _death_streak = 0;
    _death_last   = 0;
    _last_change  = 0;
}

void reset(int flag) {
    if (!flag) {
        restore_object(EMP_DIR_VAR + "arenad");
	if (!arrayp(_kill_count)) {
	    _kill_count = ({ });
	}
	if (!arrayp(_kill_streak)) {
	    _kill_streak = ({ });
	}
	if (!arrayp(_kill_last)) {
	    _kill_last = ({ });
	}
	if (!arrayp(_kill_multi)) {
	    _kill_multi = ({ });
	}
	if (!arrayp(_death_count)) {
	    _death_count = ({ });
	}
	if (!arrayp(_death_streak)) {
	    _death_streak = ({ });
	}
	if (!arrayp(_death_last)) {
	    _death_last = ({ });
	}
    }
}

int index_of(string ply, mixed arr) {
    int i, len;
    for (i = 0, len = sizeof(arr); i < len; ++i) {
	if (ply == arr[i][0]) {
	    return i;
	}
    }
    return -1;
}

mixed try_insert(string ply, int val, mixed arr) {
    int idx;
    if (sizeof(arr) >= NUM_RECORDS &&
        arr[NUM_RECORDS - 1][1] >= val) 
    {
        return 0; /* not better than worst */
    }
    if ((idx = index_of(ply, arr)) >= 0) {
        if (arr[idx][1] >= val) {
            return 0; /* did not improve self */
        }
        arr[idx] = ({ ply, val });
    } else {
        arr += ({ ({ ply, val }) });
    }
    arr = sort_array(arr, "cmp_entry");
    if (sizeof(arr) > NUM_RECORDS) {
        arr = arr[0..NUM_RECORDS - 1];
    }
    return arr;
}

int cmp_entry(mixed lhs, mixed rhs) {
    return rhs[1] - lhs[1];
}

mixed check_board(string ply, int val, mixed prev, string name) {
    mixed next;
    string str;
    if (!arrayp(next = try_insert(ply, val, prev))) {
	return prev;
    }
    _last_change = time();

    str = I_GRAMMAR->convert_ordinal_number(index_of(ply, next) + 1);
    ARN_ISLAND->broadcast(sprintf("%s took %s place on the %s leader " +
				  "board.\n", capitalize(ply), str, name));
    return next;
}

int query_kill_count_pos(object ply) {
    return index_of(ply->query_real_name(), _kill_count);
}

int query_kill_count(object ply) {
    return ply->query_property(P_KILL_COUNT);
}

int set_kill_count(object ply, int val) {
    ply->add_property(P_KILL_COUNT, val);
    return val;
}

int add_kill_count(object ply, int val) {
    return set_kill_count(ply, query_kill_count(ply) + val);
}

mixed query_kill_counts() {
    return _kill_count;
}

int query_kill_streak_pos(object ply) {
    return index_of(ply->query_real_name(), _kill_streak);
}

int query_kill_streak(object ply) {
    return ply->query_property(P_KILL_STREAK);
}

int set_kill_streak(object ply, int val) {
    ply->add_property(P_KILL_STREAK, val);
    return val;
}

int add_kill_streak(object ply, int val) {
    return set_kill_streak(ply, query_kill_streak(ply) + val);
}

mixed query_kill_streaks() {
    return _kill_streak;
}

int query_last_kill_pos(object ply) {
    return index_of(ply->query_real_name(), _kill_last);
}

int query_last_kill(object ply) {
    return ply->query_property(P_KILL_LAST);
}

int set_last_kill(object ply, int val) {
    ply->add_property(P_KILL_LAST, val);
    return val;
}

int add_last_kill(object ply, int val) {
    return set_last_kill(ply, query_last_kill(ply) + val);
}

mixed query_last_kills() {
    return _kill_last;
}

int query_multi_kill_pos(object ply) {
    return index_of(ply->query_real_name(), _kill_multi);
}

int query_multi_kill(object ply) {
    return ply->query_property(P_KILL_MULTI);
}

int set_multi_kill(object ply, int val) {
    ply->add_property(P_KILL_MULTI, val);
    return val;
}

int add_multi_kill(object ply, int val) {
    return set_multi_kill(ply, query_multi_kill(ply) + val);
}

mixed query_multi_kills() {
    return _kill_multi;
}

int query_death_count_pos(object ply) {
    return index_of(ply->query_real_name(), _death_count);
}

int query_death_count(object ply) {
    return ply->query_property(P_DEATH_COUNT);
} 

int set_death_count(object ply, int val) {
    ply->add_property(P_DEATH_COUNT, val);
    return val;
}

int add_death_count(object ply, int val) {
    return set_death_count(ply, query_death_count(ply) + val);
}

mixed query_death_counts() {
    return _death_count;
}

int query_death_streak_pos(object ply) {
    return index_of(ply->query_real_name(), _death_streak);
}

int query_death_streak(object ply) {
    return ply->query_property(P_DEATH_STREAK);
} 

int set_death_streak(object ply, int val) {
    ply->add_property(P_DEATH_STREAK, val);
    return val;
}

int add_death_streak(object ply, int val) {
    return set_death_streak(ply, query_death_streak(ply) + val);
}

mixed query_death_streaks() {
    return _death_streak;
}

int query_last_death_pos(object ply) {
    return index_of(ply->query_real_name(), _death_last);
}

int query_last_death(object ply) {
    return ply->query_property(P_DEATH_LAST);
} 

int set_last_death(object ply, int val) {
    ply->add_property(P_DEATH_LAST, val);
    return val;
}

int add_last_death(object ply, int val) {
    return set_last_death(ply, query_last_death(ply) + val);
}

mixed query_last_deaths() {
    return _death_last;
}

int query_last_change() {
    return _last_change;
}

void unlock_achievements(object ply, object foe) {
    int val;
    if (objectp(ply)) {
        EMP_D_ACHIEVEMENT->unlock(ply, "step_into_the_arena");

	val = query_kill_count(ply);
        if (EMP_D_ACHIEVEMENT->try_unlock(ply, "10_arena_kills", val, 10) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "100_arena_kills", val, 100) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "1000_arena_kills", val, 1000))
	{
	    // empty
	}
	val = query_kill_streak(ply);
        if (EMP_D_ACHIEVEMENT->try_unlock(ply, "hot_streak", val, 5) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "hotter_streak", val, 10) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "wrecking_ball", val, 20) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "the_grim_reaper", val, 30))
	{
	    // empty
	}
	val = query_multi_kill(ply);
        if (EMP_D_ACHIEVEMENT->try_unlock(ply, "double_kill", val, 2) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "triple_kill", val, 3) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "rampage", val, 4) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "godlike", val, 5))
	{
	    // empty
	}
    }
    if (objectp(foe)) {
        EMP_D_ACHIEVEMENT->unlock(foe, "mortified");

	val = query_death_count(ply);
        if (EMP_D_ACHIEVEMENT->try_unlock(ply, "10_arena_deaths", val, 10) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "100_arena_deaths", val, 100) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "1000_arena_deaths", val, 1000))
	{
	    // empty
	}
	val = query_death_streak(ply);
        if (EMP_D_ACHIEVEMENT->try_unlock(ply, "weak_streak", val, 5) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "weaker_streak", val, 10) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "humiliated", val, 20) &&
	    EMP_D_ACHIEVEMENT->try_unlock(ply, "give_up_already", val, 30))
	{
	    // empty
	}
    }
}

string desc_multi(int val) {
    switch (val) {
    case 1:  return "single";
    case 2:  return "double";
    case 3:  return "triple";
    case 4:  return "quadruple";
    default: return "IMPOSSIBLE";
    }
} 

void player_kill(object ply, object foe) {
    string ply_name, foe_name;
    if (!objectp(ply) || !interactive(ply) ||
        !objectp(foe) || !interactive(foe)) 
    {
        return;
    }
    ply_name = ply->query_real_name();
    foe_name = foe->query_real_name();
    ARN_ISLAND->broadcast(capitalize(ply_name) + " killed " + 
                          capitalize(foe_name) + "!\n");
    if (ply->query_level() > ETERNAL_LAST ||
        foe->query_level() > ETERNAL_LAST)
    {
        return;
    }
    if (query_last_kill(ply) > time() - KILL_MULTI_TIME) {
	int val;
	val = add_multi_kill(ply, 1);
	ARN_ISLAND->broadcast(capitalize(ply_name) + " got " + 
			      add_article(desc_multi(val)) + " kill!\n");
	_kill_multi = check_board(ply_name, val, _kill_multi,  "multi-kill");
    } else {
	set_multi_kill(ply, 1);
    }
    
    _kill_count = check_board(ply_name, add_kill_count(ply, 1),
			      _kill_count,  "kill-count");
    _kill_streak = check_board(ply_name, add_kill_streak(ply, 1),
			       _kill_streak,  "kill-streak");
    _kill_last = check_board(ply_name, set_last_kill(ply, time()),
			     _kill_last,  "last-kill");
    set_death_streak(ply, 0);
    
    _death_count = check_board(foe_name, add_death_count(foe, 1),
			       _death_count,  "death-count");
    _death_streak = check_board(foe_name, add_death_streak(foe, 1),
				_death_streak,  "death-streak");
    _death_last = check_board(foe_name, set_last_death(foe, time()),
			      _death_last,  "last-death");
    set_kill_streak(foe, 0);
    
    save_object(EMP_DIR_VAR + "arenad");
    unlock_achievements(ply, foe);
}

void clear_scores(object ply) {
    ply->remove_property(P_KILL_COUNT);
    ply->remove_property(P_KILL_STREAK);
    ply->remove_property(P_KILL_LAST);
    ply->remove_property(P_KILL_MULTI);
    ply->remove_property(P_DEATH_COUNT);
    ply->remove_property(P_DEATH_STREAK);
    ply->remove_property(P_DEATH_LAST);
}
