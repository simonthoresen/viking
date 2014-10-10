#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg) 
{
    mapping dat;
    object *who;
    string line, col;
    int i, len;
    who = ART_MASTER->query_members();
    if((len = sizeof(who)) == 0) {
        return notify_fail("No guild members online.");
    }
    who = sort_array(who, "cmp_player", this_object());
    if (mapp(dat = this_player()->query_property("COLOURS"))) {
        col = dat["whonames"];
    } else {
        col = 0;
    }
    write(line = sprintf("%'-'74s\n", ""));
    write("There are " + len + " Artifacts on VikingMud at " + 
          ctime(time()) + "\n");
    write(line);
    for(i = 0; i < len; ++i) {
        object ply;
        string str;
        if (!objectp(ply = who[i])) {
            continue;
        }
        str = "/com/g/who"->prefix(ply);
        if (query_idle(ply) > 30) {
            str += "I ";
        } else {
            str += "  ";
        }
        str += ply->query_pre_title();
        if (stringp(col)) {
            str += col;
        }
        str += ply->query_name();
        if (stringp(col)) {
            str += "%^END%^";
        }
        str += " " + ply->query_title();
        write(str + "\n");
    }    
    write(line);
    return 1;
}

static int
cmp_player(object lhs, object rhs) 
{
    if (lhs->query_level() > rhs->query_level()) {
        return -1;
    }
    if (lhs->query_level() < rhs->query_level()) {
        return 1;
    }
    if (lhs->query_name() < rhs->query_name()) {
        return -1;
    }
    return 0;
}

public string
short_help() 
{
    return "List all online Artifacts.";
}
