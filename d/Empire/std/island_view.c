#include "/d/Empire/empire.h"

inherit EMP_I_ISLAND_TIME;

public varargs string *
create_island_view(function symbol_fnc, mixed fnc_args...) 
{
    int row_idx, row_len;
    int col_idx, col_len;
    string *map, *ret;
    if (!arrayp(map = query_map())) {
	return 0;
    }
    if (!functionp(symbol_fnc)) {
	return copy(map);
    }
    ret = ({ });
    for (row_idx = 0, row_len = sizeof(map);
         row_idx < row_len; ++row_idx) 
    {
        string row;
	row = "";
	for (col_idx = 0, col_len = sizeof(map);
	     col_idx < col_len; ++col_idx) 
	{
	    row += sprintf("%c", call_fp(symbol_fnc, row_idx, col_idx, 
					 map[row_idx][col_idx], fnc_args...));
	}
	ret += ({ row });
    }
    return ret;
}

public varargs string *
create_area_view(int row_pos, int col_pos, int num_rows, int num_cols) 
{
    
    int row_idx, row_len;
    int col_idx, col_len;
    string *map, *ret;
    if (!arrayp(map = query_map())) {
        return 0;
    }
    ret = ({ });
    num_rows = (num_rows != 0 ? num_rows : query_view_rows()) / 2;
    num_cols = (num_cols != 0 ? num_cols : query_view_cols()) / 2;
    for (row_idx = row_pos - num_rows, row_len = row_pos + num_rows;
         row_idx <= row_len; ++row_idx) 
    {
        string row_str;
        row_str = "";
        for (col_idx = col_pos - num_cols, col_len = col_pos + num_cols;
             col_idx <= col_len; ++col_idx) 
        {
            int map_type;
            if (row_idx == row_pos && col_idx == col_pos) {
                map_type = EMP_MAP_PLAYER;
            } else {
                int row, col;
                row = max(min(row_idx, sizeof(map) - 1), 0);
                col = max(min(col_idx, strlen(map[row]) - 1), 0);
                map_type = map[row][col];
	    }
            row_str += sprintf("%c", map_type);
        }
        ret += ({ row_str });
    }
    return ret;
}

public varargs string *
create_map_view(int row_pos, int col_pos, int row_len, int col_len) 
{
    string *arr, *ret;
    int row_idx;
    if (!arrayp(arr = create_area_view(row_pos,     col_pos, 
                                       row_len - 2, col_len - 2)))
    {
        return 0;
    }
    ret = allocate(row_len);
    ret[0] = sprintf("+%'-'|*s+", col_len - 2,
                     "[ " + upper_case(query_name()) + " ]");
    for (row_idx = 1; row_idx < row_len - 1; ++row_idx) {
        ret[row_idx] = "|" + arr[row_idx - 1] + "|";
    }
    ret[row_idx] = sprintf("+%'-'*s+", col_len - 2, "");
    return ret;
}

public varargs string *
format_view(string *view, mixed ansi, mixed ansi_args...) 
{
    string *ret, row, next, prev;
    int row_idx, row_len;
    int col_idx, col_len;
    ret = ({ });
    for (row_idx = 0, row_len = sizeof(view); 
         row_idx < row_len; ++row_idx) 
    {
        row = "";
        prev = "";
        for (col_idx = 0, col_len = strlen(view[row_idx]); 
             col_idx < col_len; ++col_idx) 
        {
            int map_type, use_ansi;
            map_type = view[row_idx][col_idx];
	    if (functionp(ansi)) {
		use_ansi = call_fp(ansi, row_idx, col_idx,
				   map_type, ansi_args...);
	    } else {
		use_ansi = (ansi != 0);
	    }
	    if (use_ansi) {
		next = query_ansi_code(map_type);
	    }  else {
		next = "";
	    }
	    if (next != prev) {
		row += "%^END%^" + next;
	    }
            row += query_map_symbol(map_type);
            prev = next;
        }
        if (prev != "") {
            row += "%^END%^";
        }
        ret += ({ row });
    }
    return ret;
}

