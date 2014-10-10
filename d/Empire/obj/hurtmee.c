#include "/d/Empire/empire.h"

inherit monster I_MONSTER;
inherit math    EMP_I_MATH;

mapping _action;
int     _round_count;
int     _attack_last;
int     _attack_count;
int     _busy_count;
int     _busy_total;
int     _busy_max;
int     _dmg_count;
int     _dmg_total;
int     _dmg_max;
int    *_dmg_rounds;
int     _hit_count;
int     _hit_total;
int     _hit_max;
int    *_hit_rounds;

static void create() {
    monster::create();
    math::create();
    _action = ([ ]);
    _action["help"]     = store_fp("do_help");
    _action["skill"]    = store_fp("do_skill");
    _action["property"] = store_fp("do_property");
    _action["tmp_prop"] = store_fp("do_tmp_prop");
    _action["report"]   = store_fp("do_report");
    _action["level"]    = store_fp("do_level");
    _action["align"]    = store_fp("do_align");
    _action["kill"]     = store_fp("do_kill");
    _action["cmd"]      = store_fp("do_cmd");
    _action["str"]      = store_fp("do_str");
    _action["dex"]      = store_fp("do_dex");
    _action["con"]      = store_fp("do_con");
    _action["int"]      = store_fp("do_int");
    _action["hp"]       = store_fp("do_hp");
    _action["sp"]       = store_fp("do_sp");
    _action["wc"]       = store_fp("do_wc");
    _action["ac"]       = store_fp("do_ac");

    _round_count  = 0;
    _attack_last  = -1;
    _attack_count = 0;
    _busy_count   = 0;
    _busy_total   = 0;
    _busy_max     = 0;
    _dmg_count    = 0;
    _dmg_total    = 0;
    _dmg_max      = 0;
    _dmg_rounds   = ({ });
    _hit_count    = 0;
    _hit_total    = 0;
    _hit_max      = 0;
    _hit_rounds   = ({ });
    
    set_name("HurtmEE");
    set_long("This is the Empire Edition of Hurtme.");
    set_level(1);
    set_hp(10000);
    set_wc(0);
    set_ac(0);
    add_id("hurtme");
    set_no_corpse(1);

    add_trigger("say", store_fp("do_say"));
    
    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__damage_done", store_fp("on_damage_done"));
    add_hook("__attack", store_fp("on_attack"));
    add_hook("__kill", store_fp("on_kill"));
    add_hook("__die", store_fp("on_die"));
}

private string query_busy_report() {
    return sprintf("===> Round: %-4d  Busy:   %-4d  Max: %-3d  Total: %-5d  " +
		   "Average: %.2f\n",
                   _round_count, _busy_count, _busy_max, _busy_total, 
                   to_float(_busy_total) / to_float(_round_count + 1));
}

private string query_damage_report() {
    return sprintf("===> Round: %-4d  Damage: %-4d  Max: %-3d  Total: %-5d  " +
                   "Average: %.2f\n",
                   _round_count, _dmg_count, _dmg_max, _dmg_total, 
                   to_float(_dmg_total) / to_float(_round_count + 1));
}

private string query_hit_report() {
    return sprintf("===> Round: %-4d  Hits:   %-4d  Max: %-3d  Total: %-5d  " +
                   "Average: %.2f\n",
                   _round_count, _hit_count, _hit_max, _hit_total, 
                   to_float(_hit_total) / to_float(_round_count + 1));
}

private string stack_cols(string lhs, string rhs) {
    string *lhs_arr, *rhs_arr, *ret_arr;
    int lhs_idx, lhs_len, lhs_max;
    int rhs_idx, rhs_len;
    lhs_arr = stringp(lhs) ? explode(lhs, "\n") : ({ });
    lhs_len = sizeof(lhs_arr);
    for (lhs_idx = 0; lhs_idx < lhs_len; ++lhs_idx) {
        lhs_max = max(lhs_max, strlen(lhs_arr[lhs_idx]));
    }
    rhs_arr = stringp(rhs) ? explode(rhs, "\n") : ({ });
    rhs_len = sizeof(rhs_arr);
    
    ret_arr = ({ });
    for (lhs_idx = lhs_len > rhs_len ? 0 : -(rhs_len - lhs_len),
         rhs_idx = rhs_len > lhs_len ? 0 : -(lhs_len - rhs_len);
         lhs_idx < lhs_len && rhs_idx < rhs_len; 
         ++lhs_idx, ++rhs_idx)
    {
        ret_arr += ({ sprintf("%-*s %s", lhs_max,
                              lhs_idx >= 0 ? lhs_arr[lhs_idx] : "",
                              rhs_idx >= 0 ? rhs_arr[rhs_idx] : "") });
    }
    return join(ret_arr, "\n");
}

private string query_report() {
    return stack_cols("Damage over time:\n\n" + 
                      EMP_D_GRAPH->render_line(10, 32, _dmg_rounds),
                      "Damage histogram:\n\n" +
                      EMP_D_GRAPH->render_bins(10, 32, _dmg_rounds)) + "\n\n" +
           stack_cols("Hit count over time:\n\n" +
                      EMP_D_GRAPH->render_line(10, 32, _hit_rounds),
                      "Hit count histogram:\n\n" +
                      EMP_D_GRAPH->render_bins(10, 32, _hit_rounds)) + "\n\n" +
           query_damage_report() +
           query_hit_report() +
           query_busy_report();
}

private string *parse_arg(string arg) {
    int prev, next, len, esc;
    string *arr;
    arr = ({ });
    esc = 0;
    for (prev = 0, next = 0, len = strlen(arg); next < len; ++next) { 
        if (esc) {
            if (arg[next] == '\"') {
                esc = 0;
            }
        } else if (arg[next] == '\"') {
            esc = 1;
        } else if (arg[next] == ' ') {
            if (next > prev) {
                arr += ({ arg[prev..next - 1] });
            }
            prev = next + 1;
        } else {
            // ignore
        }
    }
    if (next > prev) {
        arr += ({ arg[prev..next - 1] });
    }
    return arr;
}

public int do_say(string arg) {
    string *arr, err;
    function fnc;
    if (!stringp(arg) || 
        !arrayp(arr = parse_arg(arg)) ||
        !functionp(fnc = _action[arr[0]])) 
    {
        return 0;
    }
    if (stringp(err = catch(call_fp(fnc, arr[1..sizeof(arr) - 1])))) {
        write(err + "\n");
    } else {
        write("Ok.\n");
    }
    return 1;
}

public void do_help() {
    write("Commands: " + make_list(sort_array(keys(_action), "sort_alpha_asc",
                                              D_FILTER)) + "\n");
}

public void do_property(string *argv) {
    if (sizeof(argv) != 2) {
        error("Usage: property <name> <mixed>");
    } 
    add_property(argv[0], to_int(argv[1]));
}

public void do_report(string *argv) {
    tell_room(environment(), "\n" + query_report() + "\n");
}

public void do_skill(string *argv) {
    if (sizeof(argv) != 2) {
        error("Usage: skill <name> <integer>");
    }
    add_skill(argv[0], to_int(argv[1]));
}

public void do_tmp_prop(string *argv) {
    if (sizeof(argv) != 2) {
        error("Usage: tmp_prop <name> <integer>");
    }
    set_tmp_prop(argv[0], to_int(argv[1]));
}

public void do_level(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: level <integer>");
    }
    set_level(to_int(argv[0]));
}

public void do_align(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: align <integer>");
    }
    set_al(to_int(argv[0]));
}

public void do_kill(string *argv) {
    command("kill " + implode(argv, " "));
}

public void do_cmd(string *argv) {
    command(implode(argv, " "));
}

public void do_str(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: str <integer>");
    }
    set_str(to_int(argv[0]));
}

public void do_dex(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: dex <integer>");
    }
    set_dex(to_int(argv[0]));
}

public void do_con(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: con <integer>");
    }
    set_con(to_int(argv[0]));
}

public void do_int(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: int <integer>");
    }
    set_int(to_int(argv[0]));
}

public void do_hp(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: hp <integer>");
    }
    set_hp(to_int(argv[0]));
}

public void do_sp(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: sp <integer>");
    }
    set_sp(to_int(argv[0]));
}

public void do_wc(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: wc <integer>");
    }
    set_wc(to_int(argv[0]));
}

public void do_ac(string *argv) {
    if (sizeof(argv) != 1) {
	error("Usage: ac <integer>");
    }
    set_ac(to_int(argv[0]));
}

static void on_heart_beat() {
    if (!objectp(query_attack())) {
	return;
    }
    /* track damage */
    tell_room(environment(), "\n" + bold(query_damage_report()));
    _dmg_rounds += ({ _dmg_count });
    _dmg_count = 0;

    /* track hit count */
    if (_hit_count > 1) {
        tell_room(environment(), bold(query_hit_report()));
    }
    _hit_rounds += ({ _hit_count });
    if (_hit_count > _hit_max) {
        _hit_max = _hit_count;
    }
    _hit_count = 0;

    /* track busy state */
    if (_attack_count == _attack_last) {
        ++_busy_count;
        ++_busy_total;
        if (_busy_count > _busy_max) {
            _busy_max = _busy_count;
        }
        tell_room(environment(), bold(query_busy_report()));
    } else {
	_attack_last = _attack_count;
        _busy_count = 0;
    }
    ++_round_count;
}

static void on_damage_done(int dmg, string type, object hitter, string loc) {
    _dmg_count += dmg;
    _dmg_total += dmg;
    if (dmg > _dmg_max) {
        _dmg_max = dmg;
    }

    ++_hit_count;
    ++_hit_total;
}

static void on_attack(object foe) {
    ++_attack_count;
}

static void on_kill(object victim, object killer) {
    do_report(0);
}

static void on_die(object corpse, object killer) {
    do_report(0);
}
