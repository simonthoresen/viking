/* http://ddowiki.com/page/Enchantment */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void
create() 
{
    ::create();
    set_info("Enchantment spells affect the minds of others, influencing or " +
             "controlling their behavior. A charm spell changes how the " +
             "subject views you, typically making it see you as a good " +
             "friend. A compulsion spell forces the subject to act in some " +
             "manner or changes the way her mind works.");
    set_train_cost(COST_ENCHANTMENT);
    add_quest_req("enchantment_0");
}
