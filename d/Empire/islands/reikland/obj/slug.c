#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("slug");
    add_long("It is green and slimy.");
    scale_level(8, 10);
    scale_hp(275, 300);
    scale_wc(13, 15);
    scale_ac(7, 8);
    set_aggressivity(40);
    set_al(random(200));
    add_property("unarmed_damage_type", ({ "acid", "acid", "blunt" }));
}
