#include "/d/Empire/islands/dragon.h"

inherit I_CONTAINER;

static void
create() 
{
    ::create();
    set_name("chest");
    set_short("an ENORMOUS granite chest");
    set_long("This is the ENORMOUS granite chest in which Onyxia keeps all " +
             "of her treasures.");
    add_id(({ "granite chest", "enormous chest" }));
    add_property(({ "artifact", "stone" }));
    set_get(0);
    set_weight(666);
    set_max_weight(666);
    set_value(666);
    set_can_open(1);
    make(C_MONEY)->add_money(4000000 + random(1000000));
    if (clonep(this_object())) {
        EMP_D_TREASURE->add_treasure(10000);
    }
}
