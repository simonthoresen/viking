/* http://ddowiki.com/page/Necromancy */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void
create() 
{
    ::create();
    set_info("Necromancy spells manipulate the power of death, unlife, and " +
             "the life force. Spells involving undead creatures make up a " +
             "large part of this school.");
    set_train_cost(COST_NECROMANCY);
    add_quest_req("necromancy_0");
}
