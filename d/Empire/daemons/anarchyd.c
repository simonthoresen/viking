#include <levels.h>
#include "/d/Empire/empire.h"

#define P_RATING      ("emp_rating")
#define NUM_RECORDS   25

inherit I_DAEMON;

mixed _rating;
int   _last_change;

void create() {
    ::create();
    _rating      = 0;
    _last_change = time();
}

void reset(int flag) {
    ::reset(flag);
    if (!flag) {
        restore_object(EMP_DIR_VAR + "anarchyd");
	if (!arrayp(_rating)) {
	    _rating = ({ });
	}
    }
}

float query_kill_chance(int k_rating, int v_rating) {
    if (k_rating < v_rating) {
        return 1.0 - query_kill_chance(v_rating, k_rating);
    }
    switch (k_rating - v_rating) {
    case 0..19:    return 0.50;
    case 20..39:   return 0.53;
    case 40..59:   return 0.58;
    case 60..79:   return 0.62;
    case 80..99:   return 0.66;
    case 100..119: return 0.69;
    case 120..139: return 0.73;
    case 140..159: return 0.76;
    case 160..179: return 0.79;
    case 180..199: return 0.82;
    case 200..299: return 0.84;
    case 300..399: return 0.93;
    default:       return 0.97;
    }
}

float query_rating_coefficient(int rating) {
    if (rating < 2000) {
        return 30.0;
    }
    if (rating < 2400) {
        return 130.0 - to_float(rating) / 20.0;
    }
    return 10.0;
}

int query_rating_change(int k_rating, int v_rating) {
    return to_int(query_rating_coefficient(k_rating) * 
                  (1.0 - query_kill_chance(k_rating, v_rating)));
}

int index_of(string ply) {
    int i, len;
    for (i = 0, len = sizeof(_rating); i < len; ++i) {
	if (ply == _rating[i][0]) {
	    return i;
	}
    }
    return -1;
}

void try_insert(string ply, int val) {
    mixed next;
    int idx;
    if (sizeof(_rating) >= NUM_RECORDS &&
        _rating[NUM_RECORDS - 1][1] >= val) 
    {
        return; /* not better than worst */
    }
    if ((idx = index_of(ply)) >= 0) {
        if (_rating[idx][1] >= val) {
            return; /* did not improve self */
        }
        _rating[idx] = ({ ply, val });
    } else {
        _rating += ({ ({ ply, val }) });
    }
    _rating = sort_array(_rating, "cmp_entry");
    if (sizeof(_rating) > NUM_RECORDS) {
        _rating = _rating[0..NUM_RECORDS - 1];
    }
    _last_change = time();
    save_object(EMP_DIR_VAR + "anarchyd");
}

int cmp_entry(mixed lhs, mixed rhs) {
    return rhs[1] - lhs[1];
}

int query_rating_pos(object ply) {
    return index_of(ply->query_real_name());
}

int query_rating(object ply) {
    int val;
    if (!objectp(ply) || (val = ply->query_property(P_RATING)) == 0) {
        return 1300;
    }    
    return val;
}

void set_rating(object ply, int val) {
    if (!objectp(ply)) {
        return;
    }
    ply->add_property(P_RATING, val);
    if (ply->query_level() > ETERNAL_LAST) {
        return;
    }
    try_insert(ply->query_real_name(), val);
}

void add_rating(object ply, int val) {
    set_rating(ply, query_rating(ply) + val);
}

mixed query_ratings() {
    return _rating;
}

int query_last_change() {
    return _last_change;
}

void player_kill(object victim, object killer) {
    int k_rating, v_rating, change;
    if (!objectp(victim) || !interactive(victim) || 
        !objectp(killer) || !interactive(killer) ||
        victim == killer) 
    {
        return;
    }
    k_rating = query_rating(killer);    
    v_rating = query_rating(victim);
    change = query_rating_change(k_rating, v_rating);
    set_rating(killer, k_rating + change);
    set_rating(victim, v_rating - change);
   
    tell_object(killer, bold("\nYou just gained " + change + " rating.\n\n"));
    tell_object(victim, bold("\nYou just lost " + change + " rating.\n\n"));
    
    EMP_D_LOG->log("anarchy", sprintf("%s (level %d, rating %d) killed " +
                                      "%s (level %d, rating %d) for %d",
                                      killer->query_real_name(), 
                                      killer->query_level(),
                                      k_rating, 
                                      victim->query_real_name(), 
                                      victim->query_level(),
                                      v_rating, change));
    EMP_D_ACHIEVEMENT->try_unlock(killer, "grand_master", 
				  k_rating + change, 2500);
}

object *query_enemies(object ply) {
    object *ret;
    if (!objectp(ply) || !interactive(ply)) {
        return 0;
    }
    ret  = ply->query_attackers();
    ret += ply->query_pre_attackers();
    ret += ply->query_fleed_from();
    return ret;
}

void enter_anarchy(object ply, object from) {
    object *arr;
    int i, len;
    if (!objectp(ply) || !interactive(ply) || 
        !objectp(from) || from->query_property("anarchy"))
    {
        return;
    }
    for (i = 0, len = sizeof(arr = query_enemies(ply)); i < len; ++i) {
        object foe;
        if (!objectp(foe = arr[i]) || foe->query_npc()) {
            continue;
        }
        if (foe->query_tmp_prop("last_vampire_hit_time") < time() - 300) {
            continue;
        }
        tell_object(ply, bold("\nYou cannot enter this area while you have " +
                              "player enemies.\n" +
                              "Make peace with them first!\n\n"));
        ply->move_player("Z", R_VOID, 1); /* bounce here from church */
        ply->move_player("Z", R_CHURCH, 1); /* bounce here from destination */
        ply->move_player("Z", from, 1);
        return;
    }
    tell_object(ply, bold("\nYou have entered an anarchy area!\n\n"));
}

void leave_anarchy(object ply, object from) {
    object *arr, obj;
    int i, len;
    if (!objectp(ply) || !interactive(ply) || 
        !objectp(from) || from->query_property("anarchy"))
    {
        return;
    }
    arr = query_enemies(ply) - ({ 0 });
    arr->remove_attackers(ply);
    arr->remove_pre_attackers(ply);
    arr->remove_fleed_from(ply);
    map_array(arr, "remove_attackers", ply);
    map_array(arr, "remove_pre_attackers", ply);
    map_array(arr, "remove_fleed_from", ply);
    tell_object(ply, bold("\nYou have left an anarchy area!\n\n"));
}
