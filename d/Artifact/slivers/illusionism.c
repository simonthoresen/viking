/* http://ddowiki.com/page/Illusion */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void 
create() 
{
    ::create();
    set_info("Illusion spells deceive the senses or minds of others. They " +
             "cause people to see things that are not there, not see things " +
             "that are there, hear phantom noises, or remember things that " +
             "never happened.");
    set_train_cost(COST_ILLUSIONISM);
    add_quest_req("illusionism_0");
}
