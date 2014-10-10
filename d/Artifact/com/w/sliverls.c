#include "/d/Artifact/artifact.h"

#define LINE79   ("----------------------------------------" + \
                  "---------------------------------------\n")
#define SPACE40  ("                                        ")

#define SLIVERS_PER_ITERATION   (50)
#define ITERATION_DELAY         (0.1)

inherit base CMD_MODULE;
inherit util EMP_I_UTIL;

private int     is_letter(int c);
private string  create_file(string arg);
private mapping create_filter(string arg);

private object  _author;
private object *_slivers;
private string  _file;

static void
create()
{
    base::create();
    util::create();
    _author  = 0;
    _slivers = 0;
    _file    = 0;
}

public int
main(string arg)
{
    if (find_call_out("generate_list") >= 0) {
        return notify_fail("Generator is busy, try again later.");
    }
    _file    = create_file(arg);
    _author  = this_player();
    _slivers = !stringp(arg) ? ART_D_SLIVER->query_slivers() : 
               call_other(ART_D_SLIVER, "query_" + explode(arg, " ")[0]);
    if (sizeof(_slivers) == 0) {
        return notify_fail("No slivers match given type.");
    }
    _slivers = filter_array(_slivers, "apply_filter", this_object(),
                            create_filter(arg));
    if (sizeof(_slivers) == 0) {
        return notify_fail("No slivers match filter.");
    }
    _slivers = sort_array(_slivers, "cmp_sliver");
    write("Generating report '" + _file + "'.\n");
    call_out("generate_list", 0, 0, -1);
    return 1;
}    

private string *
format_reqs(object obj, int width)
{
    int arr_idx, arr_len, out_idx;
    string *arr, *out;
    arr     = explode(obj->desc_reqs_short(), ", ");
    arr    -= ({ "level " + obj->query_level_req() }); 
    out     = ({ "" });
    out_idx = 0;
    for (arr_idx = 0, arr_len = sizeof(arr); arr_idx < arr_len; ++arr_idx) {
        string str;
        int str_len;
        str = capitalize(arr[arr_idx]);
        str_len = strlen(str);
        if (strlen(out[out_idx] + str) < width - 2) {
            out[out_idx] += str;
        } else {
            out += ({ str });
            ++out_idx;
        }
        if (arr_idx < arr_len - 1) {
            out[out_idx] += ", ";
        }
    }
    return out;
}

public void
generate_list(int idx, int prev_level)
{
    int cnt, len;
    if (idx == 0) {
        write_file(_file, LINE79);
    }
    len = sizeof(_slivers);
    for (cnt = 0; idx < len && cnt < SLIVERS_PER_ITERATION; ++idx, ++cnt) {
        int val;
        object obj;
        string str;
        obj = _slivers[idx];
        val = obj->query_level_req();
        if (val != prev_level) {
            str = sprintf("Level %2d  ", val);
            prev_level = val;
        } else {
            str = "          ";
        }
        str += sprintf("%-30s", obj->query_name());
        str += implode(format_reqs(obj, 40), "\n" + SPACE40);
        str += "\n";
        write_file(_file, str);
    }
    if (objectp(_author)) {
        tell_object(_author, "Report '" + _file + "' " + 
                    ((idx * 100) / len) + "% complete.\n");
    }
    if (idx < len) {
        call_out("generate_list", ITERATION_DELAY, idx, prev_level);
    } else {
        write_file(_file, LINE79);
        _author->more(_file);
    }
}

private string
create_file(string arg)
{
    int i, len;
    string out;
    out = ART_DIR_VAR + base_file_name();
    if (stringp(arg)) {
        out += ".";
        for (i = 0, len = strlen(arg); i < len; ++i) {
            out += is_letter(arg[i]) ? arg[i..i] : "_";
        }
    }
    if (file_size(out) >= 0 && !rm(out)) {
        error("Could not delete file '" + out + "'.");
    }
    return out;
}

private mapping
create_filter(string arg)
{
    int i, len, pos;
    string *arr, str;
    mapping out;
    out = ([ ]);
    if (!stringp(arg)) {
        return out;
    }
    for (i = 1, len = sizeof(arr = explode(arg, " ")); i < len; ++i) {
        str = arr[i];
        pos = find_first(':', str);
        if (pos == 0 || pos == strlen(str) - 1) {
            error("Illegal filter '" + str + "'.");
        }
        if (pos < 0) {
            out["query_" + str + "_req"] = 1;
        } else {
            out["query_" + str[0..pos - 1] + "_req"] = str[pos + 1..];
        }
    }
    EMP_DEBUG(this_player(), out);
    return out;
}

public int
apply_filter(object obj, mapping filter)
{
    int i, len;
    string *arr;
    if (!objectp(obj)) {
        return 0;
    }
    for (i = 0, len = sizeof(arr = keys(filter)); i < len; ++i) {
        if (!call_other(obj, arr[i], filter[arr[i]])) {
            return 0;
        }
    }
    return 1;
}

static int
cmp_sliver(object lhs, object rhs)
{
    return lhs->query_level_req() - rhs->query_level_req();
}

private int 
is_letter(int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
