#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

private string
format_name(string in)
{
    int i, len, esc;
    string out;
    out = "";
    for (i = 0, len = strlen(in), esc = 0; i < len; ++i) {
        if (i < len - 1 && in[i] == '%' && in[i + 1] == '^') {
            esc = 1 - esc;
            ++i;
        } else if (!esc) {
            out += in[i..i];
        }
    }
    out = capitalize(out);
    len = strlen(out);
    return len <= 39 ? out : out[0..38];
}

private string *
create_list(object ply)
{
    string *out;
    object *arr;
    int i, len;
    arr  = ply->query_worn_armour();
    arr += ({ ply->query_weapon(1), ply->query_weapon(2) });
    arr -= ({ 0 });
    len  = sizeof(arr);
    out  = allocate(len);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        out[i] = sprintf("%-39s", format_name(arr[i]->query_name()));
    }
    out  = sort_array(out, "sort_alpha_asc", D_FILTER);
    return out;
}

static int
main(string arg)
{
    object ply;
    if (wizardp(ply = this_player()) &&
        stringp(arg) &&
        !objectp(ply = find_player(arg)))
    {
        return notify_fail("No such player.");
    }
    EMP_D_LIST->write("Item                                   ",
                      create_list(ply));
    return 1;
}

public string
short_help()
{
    return "Show consumed items of power.";
}
