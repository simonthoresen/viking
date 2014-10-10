#include "/d/Empire/islands/blackrock.h"

#define P_COIN_COUNT   ("brd_coin_count")
#define P_COIN_LAST    ("brd_coin_last")
#define P_SOLVE_COUNT  ("brd_solve_count")
#define P_SOLVE_LAST   ("brd_solve_last")
#define NUM_RECORDS    (10)

inherit I_DAEMON;

public  mixed _coin_count;
public  mixed _coin_last;
public  mixed _solve_count;
public  mixed _solve_last;
private int   _last_change;

static void create() {
    ::create();
    _coin_count  = 0;
    _coin_last   = 0;
    _solve_count = 0;
    _solve_last  = 0;
    _last_change = 0;
}

private void save_me() {
    save_object(EMP_DIR_VAR + "blackrockd");
}

public void reset(int flag) {
    if (!flag) {
        restore_object(EMP_DIR_VAR + "blackrockd");
	if (!arrayp(_coin_count)) {
	    _coin_count = ({ });
	}
	if (!arrayp(_coin_last)) {
	    _coin_last = ({ });
	}
	if (!arrayp(_solve_count)) {
	    _solve_count = ({ });
	}
	if (!arrayp(_solve_last)) {
	    _solve_last = ({ });
	}
    }
}

private int index_of(string ply, mixed arr) {
    int i, len;
    for (i = 0, len = sizeof(arr); i < len; ++i) {
	if (ply == arr[i][0]) {
	    return i;
	}
    }
    return -1;
}

private mixed try_insert(string ply, int val, mixed arr) {
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

static int cmp_entry(mixed lhs, mixed rhs) {
    return rhs[1] - lhs[1];
}

private mixed check_board(string ply, int val, mixed prev, string name) {
    mixed next;
    if (!arrayp(next = try_insert(ply, val, prev))) {
	return prev;
    }
    _last_change = time();
    if (index_of(ply, prev) != (val = index_of(ply, next))) {
        string str;
        str = I_GRAMMAR->convert_ordinal_number(val + 1);
        BRD_ISLAND->broadcast(sprintf("%s took %s place on the %s leader " +
                                      "board.", capitalize(ply), str, name));
    }
    return next;
}

public varargs mixed query_coin_count(object ply) {
    return objectp(ply) ? ply->query_property(P_COIN_COUNT) : _coin_count;
}

public void set_coin_count(object ply, int val) {
    if (val <= query_coin_count(ply)) {
	return;
    }
    ply->add_property(P_COIN_COUNT, val);
    _coin_count = check_board(ply->query_real_name(), val,
			      _coin_count, "coin count");
    save_me();
}

public varargs mixed query_last_coin(object ply) {
    return objectp(ply) ? ply->query_property(P_COIN_LAST) : _coin_last;
}

public void set_last_coin(object ply, int val) {
    if (val <= query_last_coin(ply)) {
	return;
    }
    ply->add_property(P_COIN_LAST, val);
    _coin_last = check_board(ply->query_real_name(), val,
			     _coin_last, "last coin");
    save_me();
}

public varargs mixed query_solve_count(object ply) {
    return objectp(ply) ? ply->query_property(P_SOLVE_COUNT) : _solve_count;
}

public void set_solve_count(object ply, int val) {
    if (val <= query_solve_count(ply)) {
	return;
    }
    ply->add_property(P_SOLVE_COUNT, val);
    _solve_count = check_board(ply->query_real_name(), val,
                               _solve_count, "solve count");
    save_me();
}

public void add_solve_count(object ply, int val) {
    set_solve_count(ply, query_solve_count(ply) + val);
}

public varargs mixed query_last_solve(object ply) {
    return objectp(ply) ? ply->query_property(P_SOLVE_LAST) : _solve_last;
}

public void set_last_solve(object ply, int val) {
    if (val <= query_last_solve(ply)) {
	return;
    }
    ply->add_property(P_SOLVE_LAST, val);
    _solve_last = check_board(ply->query_real_name(), val,
                              _solve_last, "last solve");
    save_me();
}

public int query_last_change() {
    return _last_change;
}

public void clear_scores(object ply) {
    ply->remove_property(P_COIN_COUNT);
    ply->remove_property(P_COIN_LAST);
    ply->remove_property(P_SOLVE_COUNT);
    ply->remove_property(P_SOLVE_LAST);
}
