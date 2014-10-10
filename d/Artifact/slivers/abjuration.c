/* http://ddowiki.com/page/Abjuration */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void
create() 
{
    ::create();
    set_info("Abjurations are protective spells. They create physical or " +
             "magical barriers, negate magical or physical abilities, harm " +
             "trespassers, or even banish the subject of the spell to " +
             "another plane of existence.");
    set_train_cost(COST_ABJURATION);
    add_quest_req("abjuration_0");
}
