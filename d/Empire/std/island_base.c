#include "/d/Empire/empire.h"

#define FROZEN_FILE (resolve_path("FROZEN"))

inherit daemon I_DAEMON;
inherit hook   I_HOOK;
inherit util   EMP_I_UTIL;

private string  _name;
private string  _room_dir;
private string *_map;
private mapping _map_symbols;
private mapping _ansi_codes;
private mapping _type_names;
private mapping _block_types;
private int     _view_rows;
private int     _view_cols;

public nomask int is_frozen();

static void
create()
{
    daemon::create();
    util::create();
    _name        = 0;
    _room_dir    = 0;
    _map         = 0;
    _map_symbols = ([ EMP_MAP_PLAYER  : "@" ]);
    _ansi_codes  = ([ EMP_MAP_DEFAULT : "%^B_MAGENTA%^%^BOLD%^" ]);
    _type_names  = ([ ]);
    _block_types = ([ EMP_MAP_VOID    : 1 ]);
    _view_rows   = 7;
    _view_cols   = 13;
    if (sscanf(source_file_name(), EMP_DIR_ISLANDS + "%s/island", _name) &&
        !is_frozen())
    {
	set_heart_beat(1);
    }
}

public nomask int
is_frozen()
{
    return file_size(FROZEN_FILE) != -1;
}

public nomask int
freeze_island()
{
    if (is_frozen()) {
        return 0;
    }
    write_file(FROZEN_FILE, ctime(time()) + "\n");
    set_heart_beat(0);
    return 1;
}

public nomask int
unfreeze_island()
{
    if (!is_frozen()) {
        return 0;
    }
    rm(FROZEN_FILE);
    set_heart_beat(1);
    return 1;
}

public nomask void
enter_inv(object ply, object to, object from)
{
    if (!objectp(ply) || !living(ply) || ply->query_property(EMP_P_IGNORE)) {
	return;
    }
    if (!objectp(from) || from->query_island() != source_file_name()) {
	hook("__enter_inv", ({ ply, to, from }));
	hook("__move_player", ({ ply, 0, to }));
    } else {
	hook("__move_player", ({ ply, from, to }));
    }
    if (!objectp(present(EMP_C_BADGE, ply))) {
	make(EMP_C_BADGE, ply);
    }
}

public nomask void
leave_inv(object ply, object from, object to)
{
    if (!objectp(ply) || !living(ply) || ply->query_property(EMP_P_IGNORE)) {
	return;
    }
    if (!objectp(to) || to->query_island() != source_file_name()) {
	hook("__leave_inv", ({ ply, from, to }));
	hook("__move_player", ({ ply, from, 0 }));
    }
}

public string
query_virtual_dir()
{
    return stringp(_name) ? EMP_DIR_VAR_ISLANDS + _name + "/" : 0;
}

public int
query_num_rows()
{
    if (!arrayp(_map)) {
        return 0;
    }
    return sizeof(_map);
}

public int
query_num_cols(int row)
{
    if (!arrayp(_map) || row < 0 || row >= sizeof(_map)) {
        return 0;
    }
    return strlen(_map[row]);
}

public string
query_room(int row, int col)
{
    return sprintf("%s%d/%d", query_virtual_dir(), row, col);
}

public object
find_room(int row, int col)
{
    return find_object(query_room(row, col));
}

public object
load_room(int row, int col)
{
    return query_room(row, col)->__bootstrap();
}

public void
set_name(string val)
{
    _name = val;
}

public string
query_name()
{
    return _name;
}

public void
set_map(string *val)
{
    _map = val;
}

public void
set_map_file(string val)
{
    _map = explode(read_file(val), "\n");
}

public string
*query_map()
{
    return _map;
}

public string
query_map_row(int row)
{
    if (!arrayp(_map) || row < 0 || row >= sizeof(_map)) {
        return 0;
    }
    return _map[row];
}

public int
query_map_type(int row, int col)
{
    string str;
    if (!stringp(str = query_map_row(row))) {
        return 0;
    }
    if (col < 0 || col >= strlen(str)) {
        return 0;
    }
    return str[col];
}

public void
set_room_dir(string val)
{
    _room_dir = val;
}

public string
query_room_dir()
{
    return _room_dir;
}

public string
query_room_file(int row, int col)
{
    int map_type;
    string file;
    file = sprintf("%s%d_%d", _room_dir, row, col);
    if (file_size(file + ".c") > 0) {
        return file;
    }
    map_type = query_map_type(row, col);
    file = sprintf("%s%c", _room_dir, map_type);
    if (file_size(file + ".c") > 0) {
        return file;
    }
    file = sprintf("%smap_%c", EMP_DIR_STD, map_type);
    if (file_size(file + ".c") > 0) {
        return file;
    }
    return 0;
}

public int *
find_all_map_type_pos(int val)
{
    string *map, row;
    int row_idx, row_len, col_idx, col_len, *out;
    out = ({ });
    if (!arrayp(map = query_map())) {
	return out;
    }
    for (row_idx = 0, row_len = sizeof(map);
	 row_idx < row_len; ++row_idx)
    {
	if (!stringp(row = map[row_idx])) {
	    continue;
	}
	for (col_idx = 0, col_len = strlen(row);
	     col_idx < col_len; ++col_idx)
	{
	    if (row[col_idx] == val) {
                out += ({ to_pos(row_idx, col_idx) });
	    }
	}
    }
    return out;
}

public string *
find_all_map_type(int val)
{
    int *pos, i, len;
    string *out;
    pos = find_all_map_type_pos(val);
    out = allocate(len = sizeof(pos));
    for (i = 0; i < len; ++i) {
        out[i] = query_room(to_row(pos[i]), to_col(pos[i]));
    }
    return out;
}

public int
find_map_type_pos(int val)
{
    int *arr;
    return sizeof(arr = find_all_map_type_pos(val)) ? arr[0] : -1;
}

public string
find_map_type(int val)
{
    int pos;
    if ((pos = find_map_type_pos(val)) == -1) {
        return 0;
    }
    return query_room(to_row(pos), to_col(pos));
}

public void
set_map_symbols(mapping val)
{
    _map_symbols = val;
}

public void
add_map_symbol(int map_type, string symbol)
{
    _map_symbols[map_type] = symbol;
}

public string
query_map_symbol(int map_type)
{
    string ret;
    if (!stringp(ret = _map_symbols[map_type])) {
        ret = sprintf("%c", map_type);
    }
    return ret;
}

public void
set_ansi_codes(mapping val)
{
    _ansi_codes = val;
}

public mapping
query_ansi_codes()
{
    return _ansi_codes;
}

public void
add_ansi_code(int map_type, string code)
{
    _ansi_codes[map_type] = code;
}

public string
query_ansi_code(int map_type)
{
    string ret;
    if (!stringp(ret = _ansi_codes[map_type]) &&
	!stringp(ret = _ansi_codes[EMP_MAP_DEFAULT]))
    {
        ret = "";
    }
    return ret;
}

public void
set_block_types(mapping val)
{
    _block_types = val;
}

public mapping
query_block_types()
{
    return _block_types;
}

public void
add_block_type(int map_type)
{
    _block_types[map_type] = 1;
}

public int
query_block_type(int map_type)
{
    return _block_types[map_type];
}

public int
query_block_at(int row, int col)
{
    if (row < 0 || row >= query_num_rows() ||
        col < 0 || col >= query_num_cols(row))
    {
        return 1;
    }
    return query_block_type(query_map_type(row, col));
}

public void
set_type_names(mapping val)
{
    _type_names = val;
}

public mapping
query_type_names()
{
    return _type_names;
}

public void
add_type_name(int map_type, string type_name)
{
    _type_names[map_type] = type_name;
}

public string
query_type_name(int map_type)
{
    return _type_names[map_type];
}

public string
query_name_at(int row, int col)
{
    if (row < 0 || row >= query_num_rows() ||
        col < 0 || col >= query_num_cols(row))
    {
        return 0;
    }
    return query_type_name(query_map_type(row, col));
}

public void
set_view_rows(int val)
{
    _view_rows = val;
}

public int
query_view_rows()
{
    return _view_rows;
}

public void
set_view_cols(int val)
{
    _view_cols = val;
}

public int
query_view_cols()
{
    return _view_cols;
}

public int
has_room_files()
{
    int row_idx, row_len;
    int col_idx, col_len;
    for (row_idx = 0, row_len = query_num_rows();
         row_idx < row_len; ++row_idx)
    {
        for (col_idx = 0, col_len = query_num_cols(row_idx);
             col_idx < col_len; ++col_idx)
        {
            if (!query_block_at(row_idx, col_idx) &&
                file_size(query_room(row_idx, col_idx) + ".c") < 0)
            {
                EMP_LOG("island", sprintf("file %s not found",
                                          query_room(row_idx, col_idx)));
                return 0;
            }
        }
    }
    return 1;
}

public object *
find_livings()
{
    int row_idx, row_len;
    int col_idx, col_len;
    object *ret;
    ret = ({ });
    for (row_idx = 0, row_len = query_num_rows();
         row_idx < row_len; ++row_idx)
    {
        for (col_idx = 0, col_len = query_num_cols(row_idx);
             col_idx < col_len; ++col_idx)
        {
            object obj;
            obj = find_object(query_room(row_idx, col_idx));
            if (!objectp(obj)) {
                continue;
            }
            ret += filter_array(all_inventory(obj), "isliving", FILTER_OB);
        }
    }
    return ret;
}

public nomask void
heart_beat()
{
    hook("__heart_beat", ({ }));
}

public nomask void
reset(int flag)
{
    if (!stringp(_name)) {
        return;
    }
    if (!flag) {
	EMP_LOG("island", sprintf("island %s created", _name));
	map_array(find_livings(), "enter_inv");
    }
    hook("__reset", ({ flag }));
}

public nomask void
destroy()
{
    if (!stringp(_name)) {
        return;
    }
    hook("__destroy");
    map_array(find_livings(), "leave_inv");
    EMP_LOG("island", sprintf("island %s destroyed", _name));
}

public nomask int
is_island()
{
    return 1;
}
