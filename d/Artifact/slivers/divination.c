/* http://ddowiki.com/page/Divination */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void 
create() 
{
    ::create();
    set_info("Divination spells enable you to learn secrets long forgotten, " +
             "to predict the future, to find hidden things, and to foil " +
             "deceptive spells.");
    set_train_cost(COST_DIVINATION);
    add_quest_req("divination_0");
}
