#include "/d/Empire/islands/blackrock.h"

inherit EMP_C_ISLANDGEN;

private int     _rows;
private int     _cols;
private string *_map;
private mapping _roads;
private int     _entry;
private int     _exit;
private mapping _range;
private int     _range_max;

public void
create() 
{
    ::create();
    _rows      = 51;
    _cols      = 79;
    _map       = 0;
    _roads     = 0;
    _entry     = 0;
    _exit      = 0;
    _range     = 0;
    _range_max = 0;

    set_island("blackrock");
    set_info(store_fp("my_info"));
    push_front(store_fp("force_leave"));
    insert_after(0, store_fp("create_maze"));
    insert_after(1, store_fp("create_road_map"));
    insert_after(2, store_fp("randomize_entry"));
    insert_after(3, store_fp("create_range_map"));
    insert_after(4, store_fp("create_danger_map"));
    insert_after(5, store_fp("insert_special_rooms"));
    insert_after(6, store_fp("save_dungeon_map"));
    add_id(source_file_name());
}

static string
my_info() 
{
    string str;
    if (!stringp(str = query_island_name())) {
	return 0;
    }
    return str + " " + _rows + " x " + _cols;
}

static int
force_leave() 
{
    object *arr;
    int i, len;
    if (!arrayp(arr = BRD_ISLAND->query_livings())) {
        return 1;
    }
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        object obj;
        if (!objectp(obj = arr[i]) || 
            !living(obj) ||
            geteuid(obj) == geteuid())
        {
            continue; 
        }
        obj->move_player("X", BRD_R_ENTRY);
    }
    return 1;
}

static int
create_maze() 
{
    if (!arrayp(_map = BRD_D_MAZE->create_map(_rows, _cols))) {
        error("could not create map");
    }
    return 1;
}

static int
create_road_map() 
{
    int row, col;
    _roads = ([ ]);
    for (row = 0; row < _rows; ++row) {
        for (col = 0; col < _cols; ++col) {
            _roads[to_pos(row, col)] = (_map[row][col] == EMP_MAP_ROAD);
        }
    }
    return 1;
}

static int
randomize_entry() 
{
    _entry = keys(_roads)[random(map_sizeof(_roads))];
    return 1;
}

private int *
try_range(int pos, int val) 
{
    int row, col;
    row = to_row(pos);
    col = to_col(pos);
    if (row < 0 || row >= _rows ||
        col < 0 || col >= _cols ||
        _roads[pos] == 0 ||
        _range[pos] > 0)
    {
        return ({ });
    }
    if (val > _range_max) {
        _range_max = val;
        _exit = pos;
    }
    _range[pos] = val;
    return ({ pos });
}

static int
create_range_map() 
{
    int *heads;
    _range = ([ ]);
    for (heads = ({ _entry }); arrayp(heads); 
         heads = sizeof(heads) > 1 ? heads[1..] : 0) 
    {
        int pos, val;
        pos = heads[0];
        val = _range[pos] + 1;
        heads += try_range(add_pos(pos, to_pos(-1,  0)), val);
        heads += try_range(add_pos(pos, to_pos( 1,  0)), val);
        heads += try_range(add_pos(pos, to_pos( 0, -1)), val);
        heads += try_range(add_pos(pos, to_pos( 0,  1)), val);
    }
    return 1;
}

static int
create_danger_map() 
{
    int row, col, val;
    for (row = 0; row < _rows; ++row) {
        for (col = 0; col < _cols; ++col) {
            val = _range[to_pos(row, col)];
            _map[row][col] = val > 0 ? 
		'a' + (val * 25) / _range_max : 
		BRD_MAP_WALL;
        }
    }
    return 1;
}

static int
insert_special_rooms() 
{
    _map[to_row(_entry)][to_col(_entry)] = BRD_MAP_ENTRY;
    _map[to_row(_exit) ][to_col(_exit) ] = BRD_MAP_EXIT;
    return 1;
}

static int
save_dungeon_map() 
{
    if (file_size(BRD_MAP) >= 0 && !rm(BRD_MAP)) {
        error("Failed to delete old dungeon map.");
    }
    write_file(BRD_MAP, implode(_map, "\n") + "\n");
    return 1;
}

public void
set_rows(int val) 
{
    _rows = val;
}

public void
set_cols(int val) 
{
    _cols = val;
}
