#include "/d/Artifact/artifact.h"

inherit ART_I_APTITUDE_SKILL;

static void
create() 
{
    ::create();
    set_train_cost(COST_CHOP_APTITUDE);
}
