#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER_BORED;

public void
create_done()
{
    ::create_done();
    EMP_D_EXP->maybe_add_exp(this_object());
}
