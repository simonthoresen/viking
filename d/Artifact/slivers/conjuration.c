/* http://ddowiki.com/page/Conjuration */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void
create() 
{
    ::create();
    set_info("Conjurations bring manifestations of objects, creatures, or " +
             "some form of energy to you, actually transport creatures from " +
             "another plane of existence to your plane, heal, or create " +
             "objects or effects on the spot. Creatures you conjure " +
             "usually, but not always, obey your commands.");
    set_train_cost(COST_CONJURATION);
    add_quest_req("conjuration_0");
}
