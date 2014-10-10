#include "/d/Empire/islands/altdorf.h"
 
inherit I_TORCH;

static void
create() 
{
    ::create();
    set_name("lantern");
    set_short("a brass lantern");
    set_long("It is bulky and not nice in any way.");
    add_id("brass lantern");
    set_value(25);
    add_property("metal");
}
