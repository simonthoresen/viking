#include "/d/Empire/empire.h"

static void
create()
{
    /* empty */
}

public nomask int
starts_with(string str, string prefix)
{
    int i, len;
    if (strlen(str) < (len = strlen(prefix))) {
        return 0;
    }
    for (i = 0; i < len; ++i) {
        if (str[i] != prefix[i]) {
            return 0;
        }
    }
    return 1;
}

public varargs nomask int
find_first(int c, string arg, int off)
{
    int i, len;
    for (i = off, len = strlen(arg); i < len; ++i) {
        if (arg[i] == c) {
            return i;
        }
    }
    return -1;
}

public varargs nomask int
find_first_not(int c, string arg, int off)
{
    int i, len;
    for (i = off, len = strlen(arg); i < len; ++i) {
        if (arg[i] != c) {
            return i;
        }
    }
    return -1;
}

public nomask int
find_last(int c, string arg)
{
    int i;
    for (i = strlen(arg); --i >= 0; ) {
        if (arg[i] == c) {
            return i;
        }
    }
    return -1;
}

public nomask int
find_last_not(int c, string arg)
{
    int i;
    for (i = strlen(arg); --i >= 0; ) {
        if (arg[i] != c) {
            return i;
        }
    }
    return -1;
}

public nomask string
trim_left(string str)
{
    int pos, len;
    pos = find_first_not(' ', str);
    if (pos < 0) {
        return "";
    }
    return str[pos..];
}

public nomask string
trim_right(string str)
{
    int pos, len;
    pos = find_last_not(' ', str);
    if (pos < 0) {
        return "";
    }
    return str[..pos];
}

public nomask string
trim(string str)
{
    return trim_left(trim_right(str));
}

public nomask string
upper_case(string str)
{
    int i, len;
    for (i = 0, len = strlen(str); i < len; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 'a' - 'A';
        }
    }
    return str;
}

public nomask string *
split_string(string input, int width)
{
    string *output;
    int i, len;
    output = ({ });
    for (i = 0, len = strlen(input); i < len; i += width) {
        output += ({ input[i..i + width < len ? i + width : len - 1] });
    }
    return output;
}
