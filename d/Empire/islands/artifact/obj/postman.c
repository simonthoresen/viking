#include "/d/Empire/islands/artifact.h"

inherit EMP_I_MONSTER;

static void
create()
{
    ::create();
    set_name("Pat");
    set_short("ghost of Pat");
    set_long("This is Pat the postman. His dedication to his job has " +
             "allowed his ghost to linger in this realm of spirits to " +
             "serve your needs.");
}
