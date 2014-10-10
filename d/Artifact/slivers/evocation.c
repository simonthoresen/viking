/* http://ddowiki.com/page/Evocation */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void
create() 
{
    ::create();
    set_info("Evocation spells manipulate energy or tap an unseen source of " +
             "power to produce a desired end. In effect, they create " +
             "something out of nothing. Many of these spells produce " +
             "spectacular effects, and evocation spells can deal large " +
             "amounts of damage.");
    set_train_cost(COST_EVOCATION);
}
