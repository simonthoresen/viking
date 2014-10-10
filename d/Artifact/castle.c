#include "/d/Artifact/artifact.h"

inherit I_OBJECT;

static void 
create() 
{
    ::create();
    catch(ART_D_GLYPH->__bootstrap());
    catch(ART_D_SLIVER->__bootstrap());
}
