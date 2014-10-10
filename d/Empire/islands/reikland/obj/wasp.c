#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("fly");
    set_name("wasp");
    add_long("If you are afraid of wasps, you should probably keep away.");
    scale_level(1, 3);
    scale_dex(10, 12);
    scale_ac(1, 3);
    scale_wc(6, 8);
    set_al(-400 + random(150));
    set_aggressivity(7);
    setmin("buzzes in");
    setmout("buzzes");
    add_property("unarmed_damage_type", ({ "acid" }));
    add_property("no_headchop");
    add_property("flying");
    add_skill("prot_pierce", 95);
    add_skill("prot_slash", 5);
    add_skill("prot_chop", 5);
    add_skill("resist_slash", 20);
    add_skill("resist_chop", 20);
    add_skill("vuln_fire", 30);
    load_a_chat(15, ({ "The wasp tries to sting you!\n",
		       "The wasp looks very angry!\n" }));
}
