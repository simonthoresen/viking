#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("snake");
    add_long("It isgreen and yellow, and it is making a hizzing sound " +
             "with its split tongue.");
    scale_level(8, 10);
    scale_str(15, 17);
    scale_dex(14, 16);
    scale_hp(90, 110);
    scale_wc(17, 21);
    set_aggressive(1);
    set_al(-50);
    setmin("twirls in");
    setmout("twirls");
    add_property("unarmed_damage_type", ({ "bite", "bite", "bite", "acid" }));
}
