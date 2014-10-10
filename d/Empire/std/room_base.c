#include "/d/Empire/empire.h"

inherit room     I_ROOM;
inherit anarchy  EMP_I_ANARCHY;
inherit location EMP_I_LOCATION;

private int     _map_type;
private int     _view_cols;
private int     _view_rows;
private string *_ansi_view;
private string *_dumb_view;

static void
create()
{
    room::create();
    anarchy::create();
    location::create();
    _map_type  = 0;
    _view_rows = 0;
    _view_cols = 0;
    _ansi_view = 0;
    _dumb_view = 0;
}

static string
format_long(string desc, int term_ansi, int term_cols)
{
    string *view_arr, *desc_arr;
    int i, view_cols, desc_rows;
    if (!arrayp(view_arr = term_ansi ? _ansi_view : _dumb_view)) {
        return desc;
    }
    view_cols = _view_cols + 1;
    desc_arr = explode(break_string(stringp(desc) ? desc : "",
                                    term_cols - (view_cols + 2)), "\n");
    desc_rows = sizeof(desc_arr);
    desc = "";
    for (i = 0; i < desc_rows || i < _view_rows; ++i) {
        if (i < _view_rows) {
            desc += view_arr[i] + " ";
        } else {
            desc += sprintf("%*s", view_cols, "");
        }
        if (i < desc_rows) {
            desc += desc_arr[i];
        }
        desc += "\n";
    }
    return desc;
}

public void
set_map_type(int val)
{
    _map_type = val;
}

public int
query_map_type()
{
    return _map_type;
}

public string *
query_ansi_view()
{
    return _ansi_view;
}

public void
set_ansi_view(string *val)
{
    _ansi_view = val;
}

public string *
query_dumb_view()
{
    return _dumb_view;
}

public void
set_dumb_view(string *val)
{
    _dumb_view = val;
}

public string *
query_view(object ply)
{
    if (!objectp(ply) ||
        ply->query_property("TERM") != "ansi")
    {
        return _dumb_view;
    }
    return _ansi_view;
}

public int
query_view_cols()
{
    return _view_cols;
}

public void
set_view_cols(int val)
{
    _view_cols = val;
}

public int
query_view_rows()
{
    return _view_rows;
}

public void
set_view_rows(int val)
{
    _view_rows = val;
}
