#include "/d/Empire/empire.h"

inherit I_OBJECT;

static void
create()
{
    ::create();
    catch("/d/Empire/islands/altdorf/castle"->__bootstrap());
    catch("/d/Empire/islands/arena/castle"->__bootstrap());
    catch("/d/Empire/islands/matouci/castle"->__bootstrap());
}
