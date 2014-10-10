#include "/d/Empire/islands/altdorf.h"

inherit I_CONTAINER;

static void
create()
{
    ::create();
    set_name("thief's bag");
    set_short("a brown leather bag");
    set_long("The brown bag is made of fine leather. It can expand to " +
	     "contain alot while the bag itself is pretty light.");
    add_item(({ "leather", "fine leather" }),
	     "The fine leather on the brown bag is soft, making the bag " +
	     "extremely expandable.");
    add_id(({ "bag", "thiefs bag", "brown leather bag", "brown bag",
              "leather bag", "expandable bag", "light bag" }));
    add_property(({ "leather", "flammable" }));
    add_property("vuln_fire", 80);

    set_weight(1);
    set_value(213);
    set_max_weight(15);
}
