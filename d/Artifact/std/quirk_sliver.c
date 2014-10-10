#include "/d/Artifact/artifact.h"

inherit ART_I_SLIVER;

static void 
create() 
{
    ::create();
    set_type("quirk");
    set_slot("quirk", -1);
}
