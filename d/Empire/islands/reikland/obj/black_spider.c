#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("black spider");
    add_long("It has slime-dripping fangs. It is black and seems " +
             "to be even deadlier than most spiders of its size!");
    add_id(({ "giant spider", "spider" }));
    add_property("unarmed_damage_type",({ "bite", "pierce" }));
    scale_level(17, 20);
    scale_hp(300, 450);
    scale_wc(20, 40);
    scale_ac(5, 7);
    set_aggressive(1);
    set_al(-700 + random(200));
    setmin("crawls in");
    setmout("crawls");
}
