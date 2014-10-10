#include "/d/Empire/islands/reikland.h"

inherit RED_DIR_OBJ + "cavebat";

static void
create() 
{
    ::create();
    set_name("bat");
    add_long("An ordinary bat with brown wings.");
    remove_id("cavebat");
    set_level(query_level() / 2);
    set_aggressivity(10);
}
