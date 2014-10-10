#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("giant spider");
    add_long("It has slime-dripping fangs.");
    add_id("giant spider");
    scale_level(16, 20);
    scale_hp(250, 350);
    scale_wc(18, 22);
    scale_ac(6, 8);
    set_aggressivity(30);
    set_al(-100+random(130));
    setmin("crawls in");
    setmout("crawls");
    add_property("unarmed_damage_type",({ "bite", "pierce" }));
}
