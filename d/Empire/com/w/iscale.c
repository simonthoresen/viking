#include "/d/Empire/empire.h"

inherit cmd  CMD_MODULE;
inherit file EMP_I_FILE;

private int find_cols(string *arr) {
    int i, len, val, ret;
    ret = 0;
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        if ((val = strlen(arr[i])) > ret) {
            ret = val;
        }
    }
    return ret;
}

private string *scale_image(string *in, int out_rows, int out_cols) {
    string *out;
    int out_row, out_col;
    int in_rows, in_cols;
    in_rows = sizeof(in);
    in_cols = find_cols(in);

    out = allocate(out_rows, sprintf("%*s", out_cols, ""));
    for (out_row = 0; out_row < out_rows; ++out_row) {
        for (out_col = 0; out_col < out_cols; ++out_col) {
            int in_row, in_col;
            in_row = (out_row * in_rows) / out_rows;
            in_col = (out_col * in_cols) / out_cols;
            if (in_row < in_rows && in_col < strlen(in[in_row])) {
                out[out_row][out_col] = in[in_row][in_col];
            }
        }
    }
    return out;
}

static void create() {
    cmd::create();
    file::create();
}

static int main(string arg) {
    string file, *arr;
    int rows, cols;
    if (!stringp(arg) || sscanf(arg, "%s %d %d", file, rows, cols) != 3) {
        return notify_fail("Usage: iscale <file-name> <num-rows> <num-cols>");
    }
    if (file_size(file = this_player()->resolve_path(file)) < 0) {
        return notify_fail("File '" + file + "' not found.");
    }
    if (!stringp(arg = read_file(file)) ||
        !arrayp(arr = explode(arg, "\n"))) 
    {
        return notify_fail("File '" + file + "' has no content.");
    }
    if (cols <= 0) {
        return notify_fail("Number of columns must be at least 1.");
    }
    if (rows <= 0) {
        return notify_fail("Number of columns must be at least 1.");
    }
    write(implode(scale_image(arr, rows, cols), "\n") + "\n");
    return 1;
}
