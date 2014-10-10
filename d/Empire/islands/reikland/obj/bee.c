#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("fly");
    set_name("bee");
    add_long("The bee is just buzzing around searching for flowers to sip " +
             "nectar from.");
    add_id(({ "bee", "bug bee" }));
    scale_level(1, 4);
    scale_dex(5, 10);
    scale_ac(1, 5);
    scale_wc(1, 6);
    set_al(-75 + random(25));
    set_aggressivity(3);
    setmin("buzzes in");
    setmout("buzzes");
    add_property("unarmed_damage_type",({ "bite" }));
    add_property("unarmed_weapon_name", "teeth");
    add_property("no_headchop");
    add_property("flying");
    add_skill("prot_pierce", 95);
    add_skill("prot_slash", 5);
    add_skill("prot_chop", 5);
    add_skill("resist_pierce", 100);
    add_skill("resist_slash", 20);
    add_skill("resist_chop", 20);
    add_skill("vuln_fire", 30);
    load_a_chat(15, ({ "The bee sounds pissed off!\n",
		       "The big bee approaches you.\n" }));
}
