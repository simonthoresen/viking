#include "/d/Empire/empire.h"

inherit EMP_I_UTIL;

public varargs int add_hook(string h_name, mixed hook, mixed args);

private string  _island;
private int     _map_row;
private int     _map_col;

static void
create()
{
    object env;
    ::create();
    _island    = 0;
    _map_row   = 0;
    _map_col   = 0;
    if (sscanf(source_file_name(), EMP_DIR_VAR_ISLANDS + "%s/%d/%d",
               _island, _map_row, _map_col))
    {
        _island = EMP_DIR_ISLANDS + _island + "/island";
    }
    add_hook("__reset", store_fp("load_island"));
    add_hook("__enter_inv", store_fp("enter_island"));
    add_hook("__leave_inv", store_fp("leave_island"));
}

public varargs mixed
call_island(string fnc, mixed args...)
{
    if (!stringp(_island)) {
        return 0;
    }
    return call_other(_island, fnc, args...);
}

static void
load_island(int flag)
{
    if (!flag) {
        call_island("__bootstrap");
    }
}

public void
tell_nearby(string msg, int range)
{
    call_island("tell_nearby", _map_row, _map_col, range, msg, all_inventory());
}

public string *
find_route(int row, int col)
{
    return call_island("find_route", _map_row, _map_col, row, col);
}

public int
is_road()
{
    return call_island("is_road", this_object());
}

public mapping
query_livings_nearby(int range)
{
    return call_island("query_livings_nearby", _map_row, _map_col, range);
}

static nomask void
enter_island(object obj, object from)
{
    call_island("enter_inv", obj, this_object(), from);
}

static nomask void
leave_island(object obj, object to)
{
    call_island("leave_inv", obj, this_object(), to);
}

public void
set_island(string val)
{
    _island = val;
}

public string
query_island()
{
    return _island;
}

public string *
query_ansi_map()
{
    string *map;
    if (!stringp(_island)) {
        return 0;
    }
    map = _island->create_area_view(_map_row, _map_col, 20, 79);
    map = _island->format_view(map, 1);
    return map;
}

public void
set_ansi_map(string *val)
{
    // delete once all islands have been regenerated
}

public string *
query_dumb_map()
{
    string *map;
    if (!stringp(_island)) {
        return 0;
    }
    map = _island->create_area_view(_map_row, _map_col, 20, 79);
    map = _island->format_view(map, 0);
    return map;
}

public void
set_dumb_map(string *val)
{
    // delete once all islands have been regenerated
}

public string *
query_map(object ply)
{
    if (has_ansi(ply)) {
        return query_ansi_map();
    }
    return query_dumb_map();
}

public int
query_map_row()
{
    return _map_row;
}

public void
set_map_row(int val)
{
    _map_row = val;
}

public int
query_map_col()
{
    return _map_col;
}

public void
set_map_col(int val)
{
    _map_col = val;
}

public int
query_map_pos()
{
    return to_pos(_map_row, _map_col);
}

public void
set_map_pos(int val)
{
    _map_row = to_row(val);
    _map_col = to_col(val);
}

public int
is_empire()
{
    return 1;
}
