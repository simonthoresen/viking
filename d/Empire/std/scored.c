#include "/d/Empire/empire.h"

inherit I_DAEMON;

private string   _save_file;
private string   _prefix;
private int      _num_records;
private function _current_cmp;
public  mapping  _scores; /* = ([ "board" : ({ ({ "ply", val }), ... }) ]) */

static void
notify_entry(string board, object ply, int idx)
{
    /* empty */
}

static void
create()
{
    ::create();
    _save_file   = 0;
    _prefix      = "emp_score_";
    _num_records = 10;
    _current_cmp = 0;
    _scores      = 0;
}

public void
reset(int flag)
{
    ::reset(flag);
    if (flag || !stringp(_save_file)) {
        return;
    }
    restore_object(_save_file);
    if (!mapp(_scores)) {
        _scores = ([ ]);
    }
}

private void
save_me()
{
    if (!stringp(_save_file)) {
        error("No save file set.");
    }
    save_object(_save_file);
}

private int
index_of(string ply, mixed arr)
{
    int i, len;
    for (i = 0, len = sizeof(arr); i < len; ++i) {
	if (ply == arr[i][0]) {
	    return i;
	}
    }
    return -1;
}

private mixed
try_insert(string ply, int val, mixed arr)
{
    int idx;
    if (sizeof(arr) >= _num_records &&
        arr[_num_records - 1][1] >= val)
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
    if (sizeof(arr) > _num_records) {
        arr = arr[0.._num_records - 1];
    }
    return arr;
}

static nomask int
cmp_entry(mixed lhs, mixed rhs)
{
    if (functionp(_current_cmp)) {
        return call_fp(_current_cmp, lhs[1], rhs[1]);
    }
    return rhs[1] - lhs[1];
}

private mixed
check_board(string board, object ply, int val)
{
    mixed prev, next;
    string str;
    if (!arrayp(prev = _scores[board])) {
        prev = ({ });
    }
    str = ply->query_real_name();
    if (!arrayp(next = try_insert(str, val, prev))) {
	return prev;
    }
    if (index_of(str, prev) != (val = index_of(str, next))) {
        notify_entry(board, ply, val);
    }
    return next;
}

public nomask varargs mixed
query_score(string board, object ply)
{
    if (!stringp(board)) {
        return _scores;
    }
    if (!objectp(ply)) {
        return _scores[board];
    }
    return ply->query_property(_prefix + board);
}

public nomask varargs void
set_score(string board, object ply, int val, function cmp)
{
    if (!stringp(board) ||
        !objectp(ply) ||
        val <= query_score(board, ply))
    {
	return;
    }
    ply->add_property(_prefix + board, val);
    _current_cmp = cmp;
    _scores[board] = check_board(board, ply, val);
    save_me();
}

public varargs nomask void
clear_scores(object ply)
{
    string *arr;
    int i, len;
    for (i = 0, len = sizeof(arr = keys(_scores)); i < len; ++i) {
        ply->remove_property(_prefix + arr[i]);
    }
}

public mixed
query_highscore(string board)
{
    mixed arr;
    if (!arrayp(arr = _scores[board]) || sizeof(arr) == 0) {
        return 0;
    }
    return arr[0];
}

public int
has_highscore(string board, string name)
{
    mixed arr;
    if (!arrayp(arr = query_highscore(board))) {
        return 0;
    }
    return arr[0] == name;
}

public string *
query_highscores(string name)
{
    string *arr, *ret;
    int i, len;
    ret = ({ });
    for (i = 0, len = sizeof(arr = keys(_scores)); i < len; ++i) {
        if (!has_highscore(arr[i], name)) {
            continue;
        }
        ret += ({ arr[i] });
    }
    return ret;
}

public int
query_num_highscores(string name)
{
    return sizeof(query_highscores(name));
}

public nomask void
set_save_file(string val)
{
    _save_file = val;
}

public nomask string
query_save_file()
{
    return _save_file;
}

public nomask void
set_prefix(string val)
{
    _prefix = val;
}

public nomask string
query_prefix()
{
    return _prefix;
}

public nomask void
set_num_records(int val)
{
    _num_records = val;
}

public nomask int
query_num_records()
{
    return _num_records;
}
