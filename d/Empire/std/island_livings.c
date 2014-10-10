#include "/d/Empire/empire.h"

inherit EMP_I_ISLAND_EVENTS;

private object *_livings;

static void 
create() 
{
    ::create();
    _livings = ({ });
    add_hook("__enter_inv", store_fp("living_enters"));
    add_hook("__leave_inv", store_fp("living_leaves"));
    add_hook("__move_player", store_fp("living_moves"));
}

public string 
query_distance(int row_add, int col_add) 
{
    int val;
    val = (int)sqrt((float)(row_add * row_add + col_add * col_add));
    if (val <= 0) {
	return "";
    }
    switch (val) {
    case 1:     return "immediate ";
    case 2:     return "nearby ";
    case 3..5:  return "";
    case 6..10: return "distant ";
    default:    return "far distant ";
    }
}

public string 
query_direction(int row_add, int col_add) 
{
    if (row_add > 0) {
        if (col_add > 0) {
            return "southeast";
        } 
        if (col_add < 0) {
            return "southwest";
        }
        return "south";
    }
    if (row_add < 0) {
        if (col_add > 0) {
            return "northeast";
        } 
        if (col_add < 0) {
            return "northwest";
        }
        return "north";
    }
    if (col_add > 0) {
        return "east";
    } 
    if (col_add < 0) {
        return "west";
    }
    return 0;
}

public object *
query_livings() 
{
    _livings = _livings - ({ 0 });
    return _livings;
}

public varargs mapping 
query_livings_nearby(int row, int col, int range, int reverse_dir) 
{
    mapping ret;
    int i, len;
    ret = ([ ]);
    if (!arrayp(_livings)) {
	return ret;
    }
    for (i = 0, len = sizeof(_livings); i < len; ++i) {
        string dir;
        object ply, env;
        int row_add, col_add;
        if (!objectp(ply = _livings[i]) ||
            !objectp(env = environment(ply))) 
        {
            continue;
        }
        row_add = env->query_map_row() - row;
        col_add = env->query_map_col() - col;
        if (row_add < -range || row_add > range ||
            col_add < -range || col_add > range)
        {
            continue;
        }
	dir = query_direction(reverse_dir ? -row_add : row_add, 
			      reverse_dir ? -col_add : col_add);
	if (stringp(dir)) {
	    dir = query_distance(row_add, col_add) + dir;
	}
        if (!arrayp(ret[dir])) {
            ret[dir]  = ({ ply });
        } else {
            ret[dir] += ({ ply });
        }
    }
    return ret;
}

public varargs void 
tell_island(string msg, mixed exclude) 
{
    string name;
    if (!stringp(msg)) {
        return;
    }
    message("", msg, _livings, exclude);
}

public varargs void 
tell_nearby(int row, int col, int range, string msg, mixed exclude) 
{
    mapping dat;
    string *arr;
    int i, len;
    if (!stringp(msg) || 
	!mapp(dat = query_livings_nearby(row, col, range, 1))) 
    {
        return;
    }
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        string dir, str;
        if (!stringp(dir = arr[i])) {
            continue;
        }
        str = replace_string(msg, "#d", dir);
        str = replace_string(str, "#D", capitalize(dir));
        message("", str, dat[dir], exclude);
    }
}

public nomask void 
living_enters(object ply, object env, object from) 
{
    _livings |= ({ ply });
    _livings -= ({ 0 });
}

public nomask void 
living_leaves(object ply, object env, object to) 
{
    _livings -= ({ ply, 0 });
}

public nomask void 
living_moves(object ply, object from, object to) 
{
    int row, col;
    if (!objectp(ply) || !living(ply) || ply->query_invis()) {
	return;
    }
    if (objectp(from)) {
	row = from->query_map_row();
	col = from->query_map_col();
    } else if (objectp(to)) {
	row = to->query_map_row();
	col = to->query_map_col();
    }
    tell_nearby(row, col, 3, "There is movement to the #d.\n", ply);
}
