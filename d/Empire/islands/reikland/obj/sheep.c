#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("sheep");
    set_name("wooly sheep");
    add_long("It is minding its own bussiness.");
    scale_level(7, 9);
    scale_hp(70, 90);
    scale_wc(9, 11);
    scale_ac(2, 3);
    set_al(150);
    setmin("strolls in");
    setmout("strolls");
    add_property("unarmed_damage_type",({ "bite", "blunt" }));
}
