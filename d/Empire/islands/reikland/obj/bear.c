#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("bear");
    add_long("It is the kind of bear you do not want to be messing " +
             "around with.");
    set_al(random(100) - 50);
    setmin("crawls in");
    setmout("crawls");
    scale_level(12, 18);
    scale_str(20, 27);
    scale_dex(20, 27);
    scale_hp(250, 950);
    scale_wc(9, 14);
    scale_ac(4, 6);
    scale_skill("resist_blunt", 0, 10);
    scale_skill("resist_slash", 0, 25);
    scale_skill("resist_pierce", 0, 25);
    scale_skill("resist_cold", 0, 50);
    scale_skill("prot_cold", 0, 25);
    scale_skill("vuln_chop", 30, 0);
    scale_skill("vuln_fire", 70, 0);
    add_property("unarmed_damage_type", ({ "claw", "bite" }));
}
