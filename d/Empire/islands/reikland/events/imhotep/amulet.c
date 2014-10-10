#include "/d/Empire/islands/reikland.h"

inherit armour  EMP_I_ARMOUR;
inherit aligned EMP_I_ALIGNED;

static void 
create() 
{
    armour::create();
    aligned::create();
    set_name("Heart of Evil");
    set_short("a dark gemstone");
    set_long("This is a gemstone pendant on a leather strap. The stone is so " +
             "dark it that absorbs light. It is as large as a clenched fist, " +
             "and weights about 2 kilos.");
    add_id(({ "gemstone", "dark gemstone", "pendant", "heart" }));
    set_value(1111);
    set_weight(5);
    set_light(-1);
    set_type("amulet");
    set_max_align(ALIGN_EVIL);
    set_wear_modifier("devotion_evil", 40);
    add_property(({ "artifact", "evil" }));
}
