#include "/d/Empire/empire.h"

inherit EMP_I_STRING;

static void
create() 
{
    ::create();
}

public varargs nomask string 
dir_name(mixed arg) 
{
    int i;
    if (!stringp(arg)) {
        arg = source_file_name(arg);
    }
    if ((i = find_last('/', arg)) < 0) {
        return "/";
    }
    return arg[0..i];
}

public varargs nomask string 
base_file_name(mixed arg) 
{
    int i;
    if (!stringp(arg)) {
        arg = source_file_name(arg);
    }
    if ((i = find_last('/', arg)) < 0) {
        return arg;
    } 
    return arg[i + 1..];
}

public varargs nomask string 
resolve_path(string str, mixed env) 
{
    return dir_name(env) + str;
}

public nomask string *
get_files_absolute(string dir) 
{
    int i, len;
    string *arr;
    for (i = 0, len = sizeof(arr = get_files(dir)); i < len; ++i) {
        arr[i] = dir + arr[i];
    }
    return arr;
}

public varargs nomask void
updir(string dir, int recursive, function fnc)
{
    int i, len;
    string *arr;
    arr = get_files_absolute(dir);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        int size;
        string file;
        file = arr[i];
        size = file_size(file);
        if (functionp(fnc) && call_fp(fnc, file)) {
            continue;
        }
        if (size == -2) {
            if (recursive) {
                updir(file + "/", recursive, fnc);
            }
        } else if (size >= 0) {
            object obj;
            if (objectp(obj = find_object(file))) {
                destruct(obj);
            }
        }
    }
}

public varargs nomask void
rmdir_force(string dir) 
{
    int i, len;
    string *arr;
    arr = get_files_absolute(dir);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        int size;
        string file;
        file = arr[i];
        size = file_size(file);
        if (size == -2) {
            rmdir_force(file + "/");
        } else if (!rm(file)) {
            error("Could not delete file '" + file + "'.");
        }
    }
    if (!rmdir(dir)) {
        error("Could not delete directory '" + dir + "'.");
    }
}

public nomask void 
safe_rmdir(string dir) 
{
    if (file_size(dir) == -1) {
        return;
    }
    updir(dir, 1);
    rmdir_force(dir);
}
