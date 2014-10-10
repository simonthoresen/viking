#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN_WANDER;

static void
create() 
{
    ::create();
    set_name("citizen");
    set_short("a citizen");
    set_long("It is a citizen of Altdorf.");
    set_race("human");
    set_gender(1 + random(2));
}
