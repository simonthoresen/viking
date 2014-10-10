#include <mudlib.h>

inherit I_CONTAINER;

static void
create() 
{
    ::create();
    set_name("bag");
    set_short("a small leather bag");
    set_long("A leather bag. It is not very big, but at least it does " +
             "not weight much.");
    add_id(({ "small leather bag", "leather bag", "small bag" }));
    add_property("leather");
    set_weight(1);
    set_max_weight(7);
    set_value(50);
    add_property("tagged");
}
