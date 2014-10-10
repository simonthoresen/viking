/**
 * For readability and speed I have chosen to be a little unconventional, and 
 * keep a lot of private variables in this command module. Because noone will
 * call this function from within itself, no kittens will be harmed.
 */
#include "/d/Empire/empire.h"

#define SPACES        ("                                         " + \
                       "                                         ")
#define LEGEND_COLS   (25)
#define VIEW_ROWS     (21)
#define VIEW_COLS     (49)

inherit base CMD_MODULE;
inherit gram I_GRAMMAR;
inherit util EMP_I_UTIL;

private object  _ply;
private int     _ply_row;
private int     _ply_col;
private int     _row_min;
private int     _col_min;
private object  _env;
private string  _island;
private string *_view;
private string *_legend;
private mapping _legend_idx;
private mapping _legend_rev;
private int     _legend_res;
private mapping _bucket_map;
private mapping _bucket_pos;

static void create() {
    base::create();
    gram::create();
    util::create();
    _ply        = 0;
    _ply_row    = 0;
    _ply_col    = 0;
    _row_min    = 0;
    _col_min    = 0;
    _env        = 0;
    _island     = 0;
    _view       = 0;
    _legend     = 0;
    _legend_idx = 0;
    _legend_rev = 0;
    _legend_res = 0;
    _bucket_map = 0;
    _bucket_pos = 0;
}

private string capitalize_type(int key) {
    string str;
    if (!stringp(str = _island->query_type_name(key))) {
        return "Something";
    }
    return capitalize(str);
}

private void create_map_buckets() {
    int row, col, key, pos;
    _bucket_map = ([ ]);
    _bucket_pos = ([ ]);
    for (row = 0; row < VIEW_ROWS; ++row) {
        for (col = 0; col < VIEW_COLS; ++col) {
            key = _view[row][col];
            pos = to_pos(row, col);
            if (key >= 'A' && key <= 'Z') {
                _bucket_map[key] = pos;
                _bucket_pos[pos] = ({ capitalize_type(key) });
            } else if (key == EMP_MAP_PLAYER) {
                _bucket_map[key] = pos;
                _bucket_pos[pos] = ({ "You" });
                _legend_res = _island->query_map_type(row + _row_min,
                                                      col + _col_min);
            }
        }
    }
}

private void create_pos_buckets() {
    object *arr;
    int i, len, cnt;
    if (!arrayp(arr = _island->query_livings())) {
        return;
    }
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        object obj, env;
        int row, col, key, pos;
        if (!objectp(obj = arr[i]) || obj == _ply || obj->query_invis() ||
            !objectp(env = environment(obj)) ||
            (row = env->query_map_row() - _row_min) < 0 ||
            (row >= VIEW_ROWS) ||
            (col = env->query_map_col() - _col_min) < 0 ||
            (col >= VIEW_COLS))
        {
            continue; /* not visible */
        }
        pos = to_pos(row, col);
        if (arrayp(_bucket_pos[pos])) {
            _bucket_pos[pos] += ({ obj->query_name() });
        } else {
            _bucket_pos[pos]  = ({ obj->query_name() });
        }
    }
}

private int add_legend(int pos, int key, string *val) {
    string str;
    int tmp;
    str = make_list(val);
    if ((tmp = _legend_rev[str]) == 0) {
        while (key == _legend_res || stringp(_legend_idx[key])) {
            ++key;
        }
        tmp = key;
        _view[to_row(pos)][to_col(pos)] = tmp;  
    }
    _legend_idx[tmp] = str;
    _legend_rev[str] = tmp;
    return key;
}

private void create_legend() {
    int i, len, pos, key, *arr;
    _legend_idx = ([ ]);
    _legend_rev = ([ ]);
    for (i = 0, len = sizeof(arr = keys(_bucket_map)); i < len; ++i) {
        key = arr[i];
        pos = _bucket_map[key];
        add_legend(pos, key, _bucket_pos[pos]);
    }
    key = 'A';
    for (i = 0, len = sizeof(arr = keys(_bucket_pos)); i < len; ++i) {
        pos = arr[i];
        key = add_legend(pos, key, _bucket_pos[pos]);
    }
    _legend = ({ });
    arr = sort_array(keys(_legend_idx), "sort_asc", FILTER_OB);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        string str;
        str = "[ ] " + _legend_idx[arr[i]];
        str[1] = arr[i];
        _legend += explode(break_string(str, LEGEND_COLS - 4, "    "), "\n");
    }
}

private string render_map() {
    string str;
    int i, legend_len, view_len;
    str = sprintf("+%'-'|*s+%'-'|*s+\n", 
                  VIEW_COLS, "[ " + upper_case(_island->query_name()) + " ]",
                  LEGEND_COLS + 2, "[ LEGEND ]");
    for (i = 0, legend_len = sizeof(_legend), view_len = sizeof(_view); 
         i < legend_len || i < view_len; ++i) 
    {
        str += sprintf("|%s| %-*s |\n",
                       i < view_len ? _view[i] : SPACES[0..VIEW_COLS - 1],
                       LEGEND_COLS, i < legend_len ? _legend[i] : "");
    }
    str += sprintf("+%'-'*s+%'-'*s+\n", VIEW_COLS, "", LEGEND_COLS + 2, "");
    return str;
}

public int main(string arg) {
    if (!objectp(_ply = this_player()) ||
        !objectp(_env = environment(_ply)))
    {
        return 0; /* erm */
    }
    if (_ply->test_dark()) {
        return 1; /* block */
    }
    _ply_row = _env->query_map_row();
    _ply_col = _env->query_map_col();
    _row_min = _ply_row - VIEW_ROWS / 2;
    _col_min = _ply_col - VIEW_COLS / 2;
    if (!_env->is_empire() ||
        !stringp(_island = _env->query_island()))
    {
        return notify_fail("This is unmapped land.");
    }
    _view = _island->create_area_view(_ply_row, _ply_col, 
                                      VIEW_ROWS, VIEW_COLS);
    if (!arrayp(_view)) {
        return notify_fail("You fail.");
    }
    create_map_buckets();
    create_pos_buckets();
    create_legend();
    _view = _island->format_view(_view, has_ansi(_ply));
    tell_ansi(_ply, render_map());
    return 1;
}

string short_help() {
    return "Prints a map of the area your are in.";
}
