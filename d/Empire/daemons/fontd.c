#include "/d/Empire/empire.h"

#define DEFAULT_FONT ("roman")

inherit base I_DAEMON;
inherit util EMP_I_UTIL;

private mapping _fonts; /* ([ "name" : ([ 'char' : ({ "art", ... }) ]) ]) */

static void 
create() 
{
    base::create();
    util::create();
    _fonts = ([ ]);
}

private string 
load_file(string file) 
{
    if (file_size(file) < 0) {
        error("file '" + file + "' not found");
    }
    return read_file(file);
}

private int 
first_empty(string *arr, int from) 
{
    int i, len;
    for (i = from, len = sizeof(arr); i < len; ++i) {
        if (strlen(arr[i]) == 0) {
            break;
        }
    }
    return i;
}

private int 
first_not_empty(string *arr, int from) 
{
    int i, len;
    for (i = from, len = sizeof(arr); i < len; ++i) {
        if (strlen(arr[i]) > 0) {
            break;
        }
    }
    return i;
}

private string *
append_to(string *arr, int arr_pos, int arr_len, string *out) 
{
    int i, arr_width, out_len;
    for (i = 0, arr_width = 0; i < arr_len; ++i) {
        arr_width = max(arr_width, strlen(arr[arr_pos + i]));
    }
    out_len = sizeof(out);
    if (out_len < arr_len) {
        out += allocate(arr_len - out_len, out_len == 0 ? "" :
                        sprintf("%*s", strlen(out[0]), ""));
        out_len = arr_len;
    }
    for (i = 0; i < out_len; ++i) {
        out[i] += sprintf("%-*s", arr_width, i < arr_len ? 
                          arr[arr_pos + i] : "");
    }
    return out;
}

private string *
load_art(string file) 
{
    string *arr, *ret;
    int prev, next;
    arr = map_array(explode(load_file(file), "\n"), "trim_right");
    ret = ({ });
    for (prev = 0, next = first_empty(arr, first_not_empty(arr, prev)); 
         prev < next; 
         prev = first_not_empty(arr, next), next = first_empty(arr, prev))
    {
        ret = append_to(arr, prev, next - prev, ret);
    }
    return ret;
}

private mapping
load_inf(string file) 
{
    mapping ret;
    string *arr;
    int i, len, pos;
    ret = ([ ]);
    arr = explode(replace_string(load_file(file), "\n", " "), " ") - ({ "" });
    for (i = 0, pos = 0, len = sizeof(arr); i < len; ++i) {
        int c, cnt, arg1, arg2;
        cnt = sscanf(arr[i], "%c:%d-%d", c, arg1, arg2);
        if (cnt == 2) {
            ret[c] = ({ pos, arg1 });
            pos += arg1;
        } else if (cnt == 3) {
            ret[c] = ({ arg1, arg2 - arg1 });
            pos = arg2;
        } else {
            error("inf sequence '" + arr[i] + "' not supported");
        }
    }
    return ret;
}

private string *
slice_col(string *arr, int col_idx, int col_len) 
{
    string *ret;
    int i, len;
    len = sizeof(arr);
    ret = allocate(len);
    for (i = 0; i < len; ++i) {
        ret[i] = arr[i][col_idx..col_idx + col_len - 1];
    }
    return ret;
}

private mapping 
load_font(string name) 
{
    mapping ret, inf;
    string *art;
    int i, c, len, *arr;
    art = load_art(EMP_DIR_ETC_FONTS + name);
    inf = load_inf(EMP_DIR_ETC_FONTS + name + ".inf");
    ret = ([ ]);
    for (i = 0, len = sizeof(arr = keys(inf)); i < len; ++i) {
        c = arr[i];
        ret[c] = slice_col(art, inf[c][0], inf[c][1]);
    }
    return ret;
}

public varargs mapping 
query_font(string name) 
{
    mapping ret;
    if (!stringp(name)) {
        name = DEFAULT_FONT;
    }
    if (mapp(ret = _fonts[name])) {
        return ret;
    } 
    if (!mapp(ret = load_font(name))) {
        return 0;
    }
    _fonts[name] = ret;
    return ret;
}

private string **
resolve_chars(string str, string font_name) 
{
    string **ret;
    mapping font;
    int i, len;
    if (!mapp(font = query_font(font_name))) {
        error("font '" + font_name + "' not found");
    }
    len = strlen(str);
    ret = allocate(len);
    for (i = 0; i < len; ++i) {
        string *arr;
        if (!arrayp(arr = font[str[i]])) {
            error("char '" + str[i..i] + "' not supported");
        }
        ret[i] = arr;
    }
    return ret;
}

public varargs string *
render(string str, string font) 
{
    string **chars, *ret;
    int line_idx, num_lines;
    int char_idx, num_chars;
    if (!stringp(str)) {
        return 0;
    }
    if (!arrayp(chars = resolve_chars(str, font)) ||
        (num_chars = sizeof(chars)) == 0 ||
        (num_lines = sizeof(chars[0])) == 0)
    {
        return ({ });
    }
    ret = ({ });
    for (line_idx = 0; line_idx < num_lines; ++line_idx) {
        string str;
        str = "";
        for (char_idx = 0; char_idx < num_chars; ++char_idx) {
            str += chars[char_idx][line_idx];
            if (char_idx < num_chars - 1) {
                str += " ";
            }
        }
        ret += ({ str });
    }
    return ret;
}
