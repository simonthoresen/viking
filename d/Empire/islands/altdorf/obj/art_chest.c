#include "/d/Empire/islands/altdorf.h"

inherit I_CONTAINER;

static void
create() 
{
    ::create();
    set_name("chest");
    set_short("a large wooden chest bolted to the floor");
    set_long("It is a large wooden chest that has been bolted to the floor " +
             "to prevent theft. It contains all the artifacts that are for " +
             "sale.");
    set_get(NO_GET);
}

