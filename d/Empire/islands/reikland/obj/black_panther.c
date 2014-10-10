#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("black panther");
    add_long("Both gracious and deadly. This predator is worth running away "+
             "from in panic!");
    add_id(({ "panther", "animal" }));
    set_race("cat");
    set_aggressivity(80);
    set_al(-50 + random(50));
    scale_level(18, 23);
    scale_str(20, 25);
    scale_dex(18, 28);
    scale_int(5, 9);
    scale_wc(22, 28);
    scale_hp(400, 820);
    scale_skill("resist_cold", 5, 30);
    scale_skill("vuln_pierce", 40, 5);
    scale_skill("vuln_fire", 10, 0);
}
