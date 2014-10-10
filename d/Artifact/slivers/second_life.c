#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void 
create() 
{
    ::create();
    set_info(query_name() + " is your get-out-of-jail-free card. If you " +
             "receive a fatal hit, a d100 roll is made against your " +
             query_name() + " skill level. If your skill is higher than " +
             "the roll, you immediately loose the skill, but save your life.");
    set_train_cost(COST_SECOND_LIFE);
    add_quest_req("second_life_0");
}
