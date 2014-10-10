#include "/d/Empire/islands/artifact.h"
#include "/d/Empire/islands/chaos.h"

inherit EMP_DIR_STD + "map_d";

private object _exit;

static void
create()
{
    ::create();
    _exit = 0;
    set_long("You are in a desert. The air is heavy with sand and the smell " +
	     "of sulfur. There is a large portal here.");
    add_item(({ "portal", "large portal" }),
	     "It it an enormously large stone frame holding a swirling pink " +
	     "vortex in place.");
    add_item(({ "frame", "large frame", "stone frame" }),
	     "It is holding the vortex in place.");
    add_item(({ "vortex", "pink vortex", "swirling vortex" }),
	     "It looks intimidating.");
    add_exit(R_VOID, "portal", store_fp("go_portal"));
    add_property("no_telein");
}

static int
go_portal(string dst)
{
    object env;
    if (objectp(_exit)) {
        env = _exit;
    } else if (ART_MASTER->try_join(this_player())) {
        env = ATI_ISLAND->query_random_entry()->__bootstrap();
    } else {
        env = CAS_ISLAND->query_random_entry()->__bootstrap();
    }
    if (!objectp(env)) {
        return 0; // _P_A_R_A_N_O_I_A_
    }
    this_player()->move_player("through the portal", env);
    return 1;
}

public void
set_portal_exit(object val)
{
    _exit = val;
}

public object
query_portal_exit()
{
    return _exit;
}
