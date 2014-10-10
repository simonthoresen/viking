#include "/d/Artifact/artifact.h"

#define LINE     ("---------------------------------------")
#define COLUMN   ("                                       ")

inherit base I_ROOM;
inherit util EMP_I_UTIL;

static void
create()
{
    base::create();
    util::create();

    set_light(1);
    set_short("In the room of scores");
    set_long(store_fp("show_scores"));
    add_property("no_nothing");
}

private int
index_of(string ply, mixed score)
{
    int i, len;
    for (i = 0, len = sizeof(score); i < len; ++i) {
        if (score[i][0] == ply) {
            return i;
        }
    }
    return -1;
}

private string *
create_list(object ply, string board, mixed score)
{
    string *ret, name;
    int i, len, val;
    name = ply->query_real_name();
    ret  = ({ LINE });
    ret += ({ sprintf("%-39s", capitalize(replace_string(board, "_", " "))) });
    ret += ({ LINE });
    for (i = 0, len = sizeof(score); i < len; ++i) {
        ret += ({ sprintf("%-30s %8d", capitalize(score[i][0]),
                          score[i][1]) });
    }
    val = ART_D_SCORE->query_score(board, ply);
    if (val != 0 && index_of(name, score) < 0) {
        ret += ({ sprintf("%-30s %8d", "(" + capitalize(name) + ")", val) });
    }
    ret += ({ LINE });
    return ret;
}

private mixed
create_lists(object ply)
{
    mapping dat;
    string *arr;
    mixed ret;
    int i, len;
    dat = ART_D_SCORE->query_score();
    arr = sort_array(keys(dat), "sort_alpha_asc", FILTER_OB);
    ret = ({ });
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        ret += ({ create_list(ply, arr[i], dat[arr[i]]) });
    }
    return ret;
}

private string *
merge_lists(string *lhs, string *rhs)
{
    string *out;
    int i, lhs_len, rhs_len;
    out = ({ });
    lhs_len = sizeof(lhs);
    rhs_len = sizeof(rhs);
    for (i = 0; i < lhs_len || i < rhs_len; ++i) {
        out += ({ (i < lhs_len ? lhs[i] : COLUMN) + " " +
                  (i < rhs_len ? rhs[i] : COLUMN) });
    }
    return out;
}

static int
show_scores()
{
    mixed *arr, *out;
    int i, off, len;
    out = ({ });
    arr = create_lists(this_player());
    len = sizeof(arr);
    off = (len + 1) / 2;
    for (i = 0; i < off; ++i) {
        out += merge_lists(arr[i], i + off < len ? arr[i + off] : ({ }));
        if (i < off - 1) {
            out += ({ "" });
        }
    }
    write(implode(out, "\n") + "\n");
    return 1;
}
