#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    object ply, wpn;
    if (!objectp(wpn = ART_C_WEAPON->get_instance(this_player())) ||
        wpn->is_suspended())
    {
        write("You have no physical form.\n");
        return 1;
    }
    if (!objectp(ply = wpn->query_owner())) {
        write("You have no owner.\n");
        return 1;
    }
    write("/com/m/eq"->create_list(ply));
    return 1;
}

public string
short_help()
{
    return "Show worn and wielded equipment of your owner.";
}
