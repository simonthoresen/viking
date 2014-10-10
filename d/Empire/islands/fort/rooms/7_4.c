#include "/d/Empire/islands/fort.h"

inherit EMP_DIR_STD + "map_p";

static void
create()
{
    ::create();
    add_trigger("dig", store_fp("do_dig"));
}

static int
do_dig(string arg)
{
    object ply;
    if (!objectp(ply = this_player()) ||
        !objectp(present("shovel", ply)))
    {
        return notify_fail("You can not dig without a shovel.");
    }
    write("You dig.\n");
    say(ply->query_name() + " digs.\n");
    call_out("find_chest", 2, ply);
    return 1;
}

public void
find_chest(object ply)
{
    object obj;
    obj = make(FOR_C_TREASURE);
    message("", "You find " + obj->short() + "!\n", ply);
    message("", ply->query_name() + " finds " + obj->short() + "!\n",
            this_object(), ply);
}
