#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("panther");
    add_long("You notice how calmly this animal sneaks around in the grass. " +
             "Staring at its prey. You better hope that's not YOU!");
    add_id(({ "menacing panther", "animal" }));
    set_race("cat");
    set_aggressivity(30);
    set_al(-50 + random(50));
    scale_level(15, 19);
    scale_str(18, 20);
    scale_dex(15, 25);
    scale_int(5, 9);
    scale_wc(19, 25);
    scale_hp(300, 600);
    scale_skill("resist_cold", 5, 30);
    scale_skill("vuln_pierce", 40, 5);
    scale_skill("vuln_fire", 10, 0);
}
