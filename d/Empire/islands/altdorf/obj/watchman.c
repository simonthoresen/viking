#include "/d/Empire/islands/altdorf.h"

inherit ALT_C_GUARD;

private int _summon;
 
static void
create() 
{
    ::create();
    set_short(query_name() + " of the Altdorf Watch");
    add_id("watch");
    load_chat(5, ({ "*emote fiddles with a brass lantern.",
		    "*say Damn, it's stuck.",
		    "*sigh",
		    "*scratch" }));
    load_a_chat(50, ({ "*yell help, Heeeelp!",
		       "*yell help, help, help, heeeeelp!",
		       "*say Please stop this now.",
		       "*pant",
		       "*duck clu",
		       "*flee" }));
    add_eq(ALT_DIR_OBJ + "lantern");
    add_response(({ "clock", "time" }), store_fp("respond_time"));
}

static string 
respond_time() 
{
    return "It's " + EMP_D_TIME->query_stime() + ".";
}

public void
yell_time() 
{
    if (!objectp(environment()) || objectp(query_attack())) {
        return;
    }
    command("yell It's " + EMP_D_TIME->query_stime() + "!");
}

public int
is_watchman() 
{
    return 1;
}
