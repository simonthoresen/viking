#include "/d/Artifact/artifact.h"

inherit "/com/m/skills";

private string *
create_list(object ply)
{
    string *arr, *out;
    mapping dat;
    int i, len;
    out = ({ });
    dat = query_skills(ply);
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        if (dat[arr[i]] <= 0) {
            continue;
        }
        out += ({ sprintf("%-32s  %5s",
                          capitalize(query_skill_name(arr[i], ply)),
                          dat[arr[i]]) });
    }
    return sort_array(out, "sort_alpha_asc", FILTER_OB);
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
    EMP_D_LIST->write("Skill name                        Level",
                      create_list(ply));
    return 1;
}
