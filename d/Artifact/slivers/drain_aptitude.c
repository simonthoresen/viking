#include "/d/Artifact/artifact.h"

inherit ART_I_APTITUDE_SKILL;

static void
create() 
{
    ::create();
    set_level_req(29);
    set_train_cost(COST_DRAIN_APTITUDE);
}
