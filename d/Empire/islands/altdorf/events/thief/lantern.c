#include "/d/Empire/islands/altdorf.h"

inherit I_TORCH;

static void
create()
{
    ::create();
    set_name("thief's lantern");
    set_short("a steel lantern");
    set_long("The lantern has a very simple and crude design out of steel. "+
	     "But you guess it is sufficient for providing light.");
    add_id(({ "lantern", "simple lantern", "lit lantern", "crude lantern",
	      "thiefs lantern", "steel lantern" }));
    remove_id("torch");
    add_item(({ "design" }),
	     "Your guess is that the creator has not spent too much time " +
	     "on it.");
    add_property("steel");
    set_fuel(10000);
    set_value(75);
    set_weight(1);
}
