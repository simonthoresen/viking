/* http://ddowiki.com/page/Conjuration#Healing */
#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

static void
create() 
{
    ::create();
    set_info("Restoration involves the magical healing or augmentation of " +
             "living tissue. You can cast spells to restore health. You can " +
             "heal yourself while or after fighting with this type of spell.");
    set_train_cost(COST_RESTORATION);
}
