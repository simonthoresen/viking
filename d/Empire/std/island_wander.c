#include "/d/Empire/empire.h"

inherit EMP_I_ISLAND_VIEW;

private int    *_road_types;
private mapping _road_map;

static void
create() 
{
    ::create();
    _road_types = ({ EMP_MAP_ROAD });
}

public void 
set_road_types(int *val) 
{
    _road_types = val;
    _road_map = 0;
}

public int *
query_road_types() 
{
    return _road_types;
}

public void
add_road_type(int val) 
{
    _road_types |= ({ val });
    _road_map = 0;
}

public int
is_road_type(int val) 
{
    return (val >= 65 && val <= 90) || sizeof(({ val }) & _road_types);
}

public int
is_road_at(int row, int col) 
{
    return is_road_type(query_map_type(row, col));
}

public int
is_road(object env)
{
    return objectp(env) && is_road_at(env->query_map_row(), 
                                      env->query_map_col());
}

public varargs mapping 
create_road_map(int *road_types) 
{
    int row_idx, row_len;
    int col_idx, col_len;
    string *map, row;
    mapping paths;
    if (!arrayp(map = query_map())) {
        return 0;
    }
    if (!arrayp(road_types)) {
        road_types = _road_types;
    }
    paths = ([ ]);
    for (row_idx = 0, row_len = sizeof(map); 
         row_idx < row_len; ++row_idx) 
    {
        for (col_idx = 0, col_len = strlen(row = map[row_idx]); 
             col_idx < col_len; ++col_idx) 
        {
            if (is_road_type(row[col_idx])) {
                paths[to_pos(row_idx, col_idx)] = 1;
            }
        }
    }
    return paths;
}

public int *
find_path(int start_row, int start_col, int goal_row, int goal_col) 
{
    if (!mapp(_road_map)) {
        _road_map = create_road_map(_road_types);
    }
    return EMP_D_WANDER->calc_path(to_pos(start_row, start_col),
				   to_pos(goal_row, goal_col),
				   _road_map);
}

public string *
find_route(int start_row, int start_col, int goal_row, int goal_col) 
{
    int *path;
    if (!arrayp(path = find_path(start_row, start_col, goal_row, goal_col))) {
        return 0;
    }
    return EMP_D_WANDER->calc_route(path);
}

