#include "/d/Empire/islands/fort.h"

inherit EMP_I_ROOM;

private string _gated_exit;

static void
create()
{
    ::create();
    _gated_exit = 0;

    add_item("portcullis", store_fp("exa_portcullis"));
    add_trigger("pull", store_fp("do_pull"));
    add_hook("__reset", store_fp("change_gated_exit"));
}

static nomask void
change_gated_exit(int not_first)
{
    if (not_first || !stringp(_gated_exit)) {
        return;
    }
    change_exit(_gated_exit, EX_FUNC, store_fp("go_gate"));
}

static nomask int
go_gate(string dst)
{
    if (!wizardp(this_player()) &&
        !stringp(this_player()->query_testchar()))
    {
        write("The Gauntlet of Fort Dumbarton is not " +
              "yet open for the common public.");
        return 1;
    }
    if (!FOR_D_GATE->is_open()) {
        write("The portcullis is blocking your way.\n");
        return 1;
    }
    return 0;
}

static nomask string
exa_portcullis()
{
    string str;
    if (FOR_D_GATE->is_open()) {
        str = "It is raised.";
    } else {
        str = "It is blocking your passage " + _gated_exit + ".";
    }
    return "It is a wooden grille reinforced with metal. " + str;
}

static nomask int
do_pull(string arg)
{
    object ply;
    if (!stringp(arg) || arg != "lever") {
        return notify_fail("Pull what?");
    }
    ply = this_player();
    write("You pull the lever.\n");
    say(ply->query_name() +  " pulls the lever.\n");
    if (!FOR_D_LEVER->pull_lever(source_file_name())) {
        write("Nothing happens.\n");
    }
    return 1;
}

public void
set_gated_exit(string val)
{
    _gated_exit = val;
}

public string
query_gated_exit()
{
    return _gated_exit;
}
