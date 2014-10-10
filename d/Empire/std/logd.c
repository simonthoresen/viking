#include "/d/Empire/empire.h"

inherit EMP_I_DAEMON;

public  mapping _files;
private string  _log_dir;
private string  _save_file;

static void
create()
{
    ::create();
    _files     = ([ ]);
    _log_dir   = EMP_DIR_LOG;
    _save_file = 0;
}

private void
load_state()
{
    if (stringp(_save_file)) {
        restore_object(_save_file);
    }
    if (!mapp(_files)) {
        _files = ([ ]);
    }
}

private void
save_state()
{
    if (stringp(_save_file)) {
        save_object(_save_file);
    }
}

public void
reset(int flag)
{
    ::reset(flag);
    if (flag) {
        load_state(); // load on initial reset
    }
}

private string
resolve_file(string file)
{
    if (!stringp(file) || strlen(file) == 0) {
        return 0;
    }
    if (file[0] != '/') {
        file = _log_dir + file;
    }
    return file;
}

public int
add_watcher(string file, string name)
{
    if (!stringp(file = resolve_file(file))) {
        return 0;
    }
    if (!arrayp(_files[file])) {
        _files[file] = ({ });
    }
    _files[file] |= ({ name });
    save_state();
    return 1;
}

public int
remove_watcher(string file, string name)
{
    if (!stringp(file = resolve_file(file))) {
        return 0;
    }
    if (!arrayp(_files[file])) {
	return 0;
    }
    _files[file] -= ({ name });
    save_state();
    return 1;
}

public int
is_watching(string file, string name)
{
    string *arr;
    if (!stringp(file = resolve_file(file))) {
        return 0;
    }
    return arrayp(arr = _files[file]) && member_array(name, arr) >= 0;
}

public string *
query_files()
{
    return filter_array(get_files(_log_dir), "can_watch", this_object());
}

static int
can_watch(string file)
{
    return arrayp(_files[_log_dir + file]);
}

public varargs void
log(string file, string str, mixed args...)
{
    if (!stringp(file = resolve_file(file)) || !stringp(str)) {
        return;
    }
    if (!arrayp(_files[file])) {
	_files[file] = ({ });
        save_state();
    }
    if (sizeof(args) > 0) {
        str = sprintf(str, args...);
    }
    message("channels", "[" + file + "]: " + str + "\n",
            map_array(_files[file], "find_watcher", this_object()));
    log_file(file, str + "\n");
}

static object
find_watcher(string arg)
{
    return find_player(arg);
}

public nomask void
set_log_dir(string val)
{
    _log_dir = val;
}

public nomask string
query_log_dir()
{
    return _log_dir;
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
