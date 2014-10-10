#include "/d/Empire/islands/altdorf.h"

inherit I_ARMOUR;

static void
create() 
{
    ::create();
    set_name("buckler");
    add_id("buckler");
    set_short("a buckler");
    set_long("This buckler is a shield worn on the forearm. It looks like " +
             "it would provide a lot of protection.");
    add_property(({ "iron", "tagged", "hidden" }));
    set_type("shield");
    set_value(1111);
    set_weight(2);
    add_property("protected", 95);
    set_wear_modifier("ac", 2, 666);
    set_ac(1);
}
