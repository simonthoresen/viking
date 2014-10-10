#include "/d/Empire/islands/fort.h"

inherit EMP_I_DAEMON;

private int _num_deaths;

static void
create()
{
    ::create();
    _num_deaths = 0;
}

public void
register_death(object corpse, object killer)
{
    ++_num_deaths;
}

public void
add_num_deaths(int val)
{
    _num_deaths += val;
}

public int
query_num_deaths()
{
    return _num_deaths;
}

public object
new_instance(string wing)
{
    object npc;
    switch (wing) {
    case "goblin":
    case "orc":
    case "troll":
    case "ogre":
        npc = new("/players/khaine/open/fort_guard");
        break;
    default:
        error(sprintf("unknown wing %O", wing));
    }
    if (!npc<-FOR_I_MONSTER) {
        error(sprintf("%O does not inherit %O",
                      npc, FOR_I_MONSTER));
    }
    npc->set_dangerlevel(_num_deaths / 5);
    npc->add_hook("__die", store_fp("register_death"));
    return npc;
}
