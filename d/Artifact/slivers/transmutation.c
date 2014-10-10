/* http://ddowiki.com/page/Transmutation */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void
create() 
{
    ::create();
    set_info("Transmutation spells change the properties of some creature, " +
             "thing, or condition.");
    set_train_cost(COST_TRANSMUTATION);
    add_quest_req("transmutation_0");
}
