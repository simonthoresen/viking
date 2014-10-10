#include "/d/Empire/islands/fort.h"

inherit EMP_I_DAEMON;

private object *_npcs;

static void
create()
{
    ::create();
    _npcs = ({ });
}

private void
update_dangerlevel()
{
    _npcs -= ({ 0 });
    _npcs->set_dangerlevel(100 - (100 * (sizeof(_npcs) - 1)) / FOR_NUM_WINGS);
}

public void
register_death()
{
    _npcs -= ({ previous_object() });
    update_dangerlevel();
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
        npc = new("/players/khaine/open/fort_boss");
        break;
    default:
        error(sprintf("unknown wing %O", wing));
    }
    if (!npc<-FOR_I_MONSTER) {
        error(sprintf("%O does not inherit %O",
                      npc, FOR_I_MONSTER));
    }
    _npcs += ({ npc });
    npc->add_hook("__destroy", store_fp("register_death"));
    update_dangerlevel();
    return npc;
}
