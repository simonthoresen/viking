#include "/d/Empire/empire.h"

#define ROOMS_PER_ITERATION   (32)
#define ITERATION_DELAY       (0.1)

#define FMT_DUMB              (0)
#define FMT_ANSI              (store_fp("use_ansi"))

inherit EMP_C_TASKLIST;

private string _island;
private string _log_file;
private int    _unloaded;
private int    _created;

static void
create()
{
    ::create();
    _island   = 0;
    _log_file = 0;
    _unloaded = 0;
    _created  = 0;

    set_info(store_fp("query_island_name"));
    push_back(store_fp("begin_unload"));
    push_back(store_fp("await_unload"));
    push_back(store_fp("begin_create"));
    push_back(store_fp("await_create"));
    push_back(store_fp("reload_island"));
}

static string
query_island_name()
{
    string *arr;
    if (!stringp(_island)) {
        return 0;
    }
    arr = explode(_island, "/");
    return arr[sizeof(arr) - 2];
}

static void
do_notify(string str)
{
    string file;
    ::do_notify(str);
    if (stringp(_log_file)) {
        EMP_LOG(_log_file, str);
    }
}

private mapping
query_area(int row, int col)
{
    int row_idx, col_idx;
    mapping dat;
    dat = ([ ]);
    for (row_idx = row - 1; row_idx <= row + 1; ++row_idx) {
        for (col_idx = col - 1; col_idx <= col + 1; ++col_idx) {
            string str, dir;
            if (!stringp(str = _island->query_name_at(row_idx, col_idx)) ||
                !stringp(dir = _island->query_direction(row_idx - row,
                                                        col_idx - col)))
            {
                continue;
            }
            if (!arrayp(dat[str])) {
                dat[str]  = ({ dir });
            } else {
                dat[str] += ({ dir });
            }
        }
    }
    return dat;
}

private string
create_area_long(int row, int col)
{
    string *type_keys, *desc, *dirs, type;
    mapping type_map;
    int i, len;
    if (!mapp(type_map = query_area(row, col))) {
        return 0;
    }
    desc = ({ });
    if (stringp(type = _island->query_name_at(row, col)) &&
        arrayp(dirs = type_map[type]))
    {
        desc += ({ "The " + type + " continues to the " +
                   make_list(dirs) + "." });
        type_map[type] = 0;
    }
    for (i = 0, len = sizeof(type_keys = keys(type_map)); i < len; ++i) {
        type = type_keys[i];
        dirs = type_map[type];
        desc += ({ capitalize(add_article(type)) + " lies to the " +
                   make_list(dirs) + "." });
    }
    return implode(desc, " ");
}

private string
create_exit_code(int row, int col, string dir, int invis)
{
    if (_island->query_block_at(row, col)) {
        return 0;
    }
    return sprintf("add_exit(%O, %O, 0, 0, 0, %d)",
                   _island->query_room(row, col), dir, invis);
}

private string *
format_view(string *view, int ansi)
{
    return map_array(_island->format_view(view, ansi), "format_view_line");
}

static string
format_view_line(string str)
{
    return replace_string(str, "\\", "\\\\");
}

private string
create_source_code(int row, int col)
{
    string *head, *body, *view, *exits;
    string file, err;
    object room;
    int invis;
    if (!stringp(file = _island->query_room_file(row, col))) {
        abort(sprintf("Unknown map type '%c' at (%d, %d).",
                      _island->query_map_type(row, col), row, col));
        return 0;
    }
    if (!objectp(room = call_other(file, "__bootstrap"))) {
        abort(sprintf("Room '%s' does not load.\n", file));
        return 0;
    }
    head = ({ "inherit room \"" + file + "\"" });
    if (room->is_empire()) {
        view = _island->create_area_view(row, col);
        body = ({
            sprintf("set_area_long(%O)", create_area_long(row, col)),
            sprintf("set_map_type(%d)",  _island->query_map_type(row, col)),
            sprintf("set_dumb_view(%O)", format_view(view, 0)),
            sprintf("set_ansi_view(%O)", format_view(view, 1)),
            sprintf("set_view_cols(%d)", _island->query_view_cols()),
            sprintf("set_view_rows(%d)", _island->query_view_rows()),
        });
    } else {
        head += ({ "inherit anarchy EMP_I_ANARCHY",
                   "inherit location EMP_I_LOCATION" });
        body  = ({ "anarchy::create()",
                   "location::create()" });
    }
    exits = ({
        create_exit_code(row - 1, col,     "north", 0),
        create_exit_code(row,     col - 1, "west",  0),
        create_exit_code(row,     col + 1, "east",  0),
        create_exit_code(row + 1, col,     "south", 0)
    });
    body += exits;
    invis = sizeof(exits - ({ 0 }));
    exits = ({
        create_exit_code(row - 1, col - 1, "northwest", invis),
        create_exit_code(row - 1, col + 1, "northeast", invis),
        create_exit_code(row + 1, col - 1, "southwest", invis),
        create_exit_code(row + 1, col + 1, "southeast", invis)
    });
    body += exits;

    return
        "#include \"/d/Empire/empire.h\"\n" +
        implode(head, ";\n") + ";\n" +
        "void create() {\n" +
        "    room::create();\n" +
        "    " + implode(body, ";\n    ") + ";\n" +
        "}\n";
}

private string
query_virtual_dir()
{
    string str;
    str = _island->query_virtual_dir();
    if (!sscanf(str, EMP_DIR_VAR + "%*s")) {
        error("Unsupported virtual dir '" + str + "'.");
    }
    return str;
}

public int
use_ansi(int row, int col, int type, int row_len, int col_len)
{
    return row > 0 && row < 22 && col > 0 && col < 78;
}

public void
unload_rooms(int row_idx)
{
    string path, err;
    if (row_idx >= _island->query_num_rows()) {
        _unloaded = 1;
        return;
    }
    notify("unload_rooms(%d)", row_idx);
    path = query_virtual_dir() + row_idx + "/";
    if (file_size(path) == -2 && stringp(err = catch(safe_rmdir(path)))) {
        abort(err);
        return;
    }
    call_out("unload_rooms", ITERATION_DELAY, row_idx + 1);
}

public void
create_rooms(int row_idx, int col_idx)
{
    int row_len, col_len, cnt;
    string row;
    notify("create_rooms(%d, %d)", row_idx, col_idx);
    for (cnt = 0; cnt < ROOMS_PER_ITERATION; ++cnt) {
        if (col_idx >= _island->query_num_cols(row_idx)) {
            col_idx = 0;
            ++row_idx;
        }
        if (row_idx >= _island->query_num_rows()) {
            _created = 1;
            return;
        }
        if (!_island->query_block_at(row_idx, col_idx)) {
            string code, path;
            if (!stringp(code = create_source_code(row_idx, col_idx))) {
                return; /* aborted */
            }
            path = query_virtual_dir() + row_idx;
            if (file_size(path) == -1 && !mkdir(path)) {
                abort("Could not create directory '" +
                      path + "'.");
                return;
            }
            if (!write_file(path + "/" + col_idx + ".c", code)) {
                abort("Could not create file '" +
                      path + "/" + col_idx + "'.");
                return;
            }
        }
        ++col_idx;
    }
    call_out("create_rooms", ITERATION_DELAY, row_idx, col_idx);
}

static int
begin_unload()
{
    object *arr;
    _island->freeze_island();
    if (arrayp(arr = _island->query_critters())) {
        arr->move_player("X", R_VOID);
    }
    call_out("unload_rooms");
    return 1;
}

static int
await_unload()
{
    object obj;
    string str;
    if (!_unloaded) {
        return 0;
    }
    str = query_virtual_dir();
    if (objectp(obj = find_object(_island))) {
        destruct(obj);
    }
    safe_rmdir(str);
    return 1;
}

static int
begin_create()
{
    if (!mkdir(_island->query_virtual_dir())) {
        error("Could not create virtual island directory.");
    }
    call_out("create_rooms");
    return 1;
}

static int
await_create()
{
    return _created;
}

static int
reload_island()
{
    object obj;
    if (objectp(obj = find_object(_island))) {
        destruct(obj);
    }
    _island->unfreeze_island();
    return 1;
}

public void
set_island(string val)
{
    if (stringp(val)) {
        if (val[0] != '/') {
            val = EMP_DIR_ISLANDS + val;
        }
        if (file_size(val) == -2) {
            val = val + "/island";
        }
        if (file_size(val + ".c") < 0) {
            error("Island '" + val + "' not found.");
        }
    }
    _island = val;
}

public string
query_island()
{
    return _island;
}

public void
set_log_file(string val)
{
    _log_file = val;
}

public string
query_log_file()
{
    return _log_file;
}
