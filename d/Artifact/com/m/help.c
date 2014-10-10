#include "/d/Artifact/artifact.h"

#define SPACES ("          ")

inherit EMP_I_COMMAND;

private string *
append_to(string in, int width, string *out)
{
    int in_idx, in_len, out_idx, out_len, str_len;
    string *in_arr, out_str, str;
    out_idx = sizeof(out) - 1;
    for (in_idx = 0, in_len = sizeof(in_arr = explode(in, " "));
         in_idx < in_len; ++in_idx)
    {
        str = in_arr[in_idx];
        str_len = strlen(str);
        if (str_len == 0) {
            continue;
        }
        out_str = out[out_idx];
        out_len = strlen(out_str);
        if (out_len + str_len < width) {
            if (out_len > 0 && out_str[out_len - 1] != ' ') {
                out_str += " ";
            }
            out_str += str;
            out[out_idx] = out_str;
        } else {
            out += ({ "" + str });
            ++out_idx;
        }
    }
    return out;
}

private void
process_tag(string str)
{
    string arg;
    str = trim(str);
    EMP_DEBUG(this_player(), str);
    if (sscanf(str, "@unlocks %s", arg) == 1) {
        ART_D_QUEST->unlock(this_player(), arg);
    } else {
        error("Tag '" + str + "' not supported.");
    }
}

private string *
build_paragraphs(string *in, int width)
{
    int in_idx, in_len;
    string *out;
    out = ({ "" });
    for (in_idx = 0, in_len = sizeof(in); in_idx < in_len; ++in_idx) {
        string str;
        int str_len;
        str = trim(in[in_idx]);
        str_len = strlen(str);
        if (str_len == 0) {
            if (strlen(out[sizeof(out) - 1]) > 0) {
                out += ({ "","" });
            }
        } else if (str[0] == '@') {
            if (str == "@pre") {
                return out + in[in_idx + 1..in_len - 1];
            }
            process_tag(str);
        } else {
            if (str[0] == '\f') {
                str  = str_len > 1 ? str[1..] : "";
                out += ({ "" });
            }
            out = append_to(str, width, out);
        }
    }
    return out;
}

private string
to_singular(string str)
{
    int len;
    len = strlen(str);
    return len > 1 && str[len - 1] == 's' ? str[0..len - 2] : str;
}

private mapping
query_topics()
{
    int i, len;
    string *arr;
    mapping dat;
    arr = get_files(ART_DIR_ETC_HELP);
    dat = ([ ]);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        dat[arr[i]] = arr[i];
        dat[to_singular(arr[i])] = arr[i];
    }
    COM_D->assure_dir_loaded(ART_DIR_COM_M);
    arr = keys(COM_D->dump_path(ART_DIR_COM_M));
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        dat[arr[i]] = arr[i];
        dat[to_singular(arr[i])] = arr[i];
    }
    return dat;
}

private void
maybe_see_also(string word, mapping topics, mapping out)
{
    string topic;
    if (stringp(topic = topics[word])) {
        out[topic] = 1;
    }
}

private int
is_letter(int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

private string
build_see_also(string desc, int width, int indent)
{
    int prev, next, len;
    mapping topics, dat;
    dat = ([ ]);
    topics = query_topics();
    for (prev = 0, next = 0, len = strlen(desc); next < len; ++next) {
        if (!is_letter(desc[next])) {
            maybe_see_also(desc[prev..next - 1], topics, dat);
            prev = next + 1;
        }
    }
    if (prev < next) {
        maybe_see_also(desc[prev..next - 1], topics, dat);
    }
    return break_string(make_list(keys(dat)), width, indent);
}

private string
build_description(string str, int width, int indent)
{
    string *arr;
    arr = explode(str, "\n");
    arr = build_paragraphs(arr, width);
    return implode(arr, "\n          "[0..indent]);
}

private string
try_file(string arg)
{
    if (!stringp(arg)) {
        return 0;
    }
    if (file_size(arg = ART_DIR_ETC_HELP + arg) < 0 &&
        file_size(arg = arg + "s") < 0)
    {
        return 0;
    }
    return read_file(arg);
}

private string
try_sliver(string arg)
{
    object obj;
    if (!objectp(obj = ART_D_SLIVER->query_sliver(arg))) {
        return 0;
    }
    switch (obj->query_type()) {
    case "glyph":
    case "skill":
    case "spell":
        return obj->query_info() + "\n\n" +
               obj->desc_reqs_long();

    case "quirk":
    case "shape":
        return obj->query_info() + "\n\n" +
               obj->desc_reqs_long() + "\n\f" +
               obj->desc_slots_long();

    default:
        return 0;
    }
}

static int
main(string arg)
{
    string desc, see_also;
    if (arg == "topic" || arg == "topics") {
        write(break_string(make_list(keys(query_topics())), 79));
        return 1;
    }
    if (!stringp(arg)) {
        return 0;
    }
    if (!stringp(desc = try_file(arg)) &&
        !stringp(desc = try_sliver(arg)))
    {
        return 0;
    }
    desc = build_description(desc, 75, 4);
    see_also = build_see_also(desc, 75, 4);
    printf("TITLE\n" +
           "    %s\n\n" +
           "DESCRIPTION\n" +
           "    %s\n\n" +
           "SEE ALSO\n" +
           "    %s\n",
           capitalize(arg), desc, see_also);
    return 1;
}

public string
short_help()
{
    return "Show information about a topic.";
}
