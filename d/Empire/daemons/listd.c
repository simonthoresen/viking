#include "/d/Empire/empire.h"

#define TERM_WIDTH (80)

inherit EMP_I_DAEMON;

private string _hrule;
private string _space;

static void
create()
{
    ::create();
    _hrule = sprintf("%'-'*s", TERM_WIDTH, "");
    _space = sprintf("%' '*s", TERM_WIDTH, "");
}

private string
repeat(string str, string delim, int cnt)
{
    int i;
    string out;
    out = str;
    for (i = 1; i < cnt; ++i) {
        out += delim + str;
    }
    return out;
}

public int
calc_num_rows(int num_items, int num_cols)
{
    return (num_items + (num_cols - 1)) / num_cols; // round up
}

public int
calc_num_cols(int num_items, int col_width)
{
    int num_cols;
    for (num_cols = TERM_WIDTH / (col_width + 1);
         num_cols > 1 && calc_num_rows(num_items, num_cols) < 5;
         num_cols--)
    {
        // empty
    }
    return num_cols;
}

public string
format(string header, string *items, int is_ansi)
{
    int col_width;
    string hrule;
    col_width = strlen(header);
    if (col_width >= TERM_WIDTH) {
        // the column is too wide for the terminal, but insead of raising
        // an error, lets just do a best effort item dump
        hrule = sprintf("%'-'*s", TERM_WIDTH - 1, "");
    } else {
        int num_items, num_cols, num_rows;
        string space;
        num_items = sizeof(items);
        num_cols  = calc_num_cols(num_items, col_width);
        num_rows  = calc_num_rows(num_items, num_cols);
        space     = _space[0..(TERM_WIDTH - num_cols * (col_width + 1)) /
                           num_cols];
        hrule     = repeat(_hrule[0..col_width - 1], space, num_cols);
        header    = repeat(header, space, num_cols);
        if (num_cols > 1) {
            int row, col, idx;
            string *out;
            out = allocate(num_rows);
            for (row = 0; row < num_rows; ++row) {
                out[row] = "";
                for (col = 0; col < num_cols; ++col) {
                    idx = row + num_rows * col;
                    if (idx < num_items) {
                        out[row] += items[idx];
                    }
                    if (col < num_cols - 1) {
                        out[row] += space;
                    }
                }
            }
            items = out;
        }
    }
    return hrule + "\n" +
           header + "\n" +
           hrule + "\n" +
           implode(items, "\n") + "\n" +
           hrule + "\n";
}

public void
write(string header, string *items)
{
    ::write(format(header, items, 0));
}

public void
write_ansi(string header, string *items)
{
    ::write_ansi(format(header, items, 1));
}
