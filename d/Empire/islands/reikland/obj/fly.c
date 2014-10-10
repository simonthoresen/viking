#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("fly");
    set_name("fly");
    add_long("It is flying around in circles.");
    scale_level(1, 3);
    scale_dex(8, 10);
    scale_ac(0, 2);
    scale_wc(1, 2);
    set_al(0);
    setmin("flies in");
    setmout("flies");
    add_property("unarmed_damage_type",({ "blunt" }));
    add_property("no_headchop");
    add_property("flying");
    add_skill("prot_pierce", 95);
    add_skill("prot_slash", 5);
    add_skill("prot_chop", 5);
    add_skill("resist_pierce", 100);
    add_skill("resist_slash", 20);
    add_skill("resist_chop", 20);
    add_skill("vuln_fire", 30);
    load_a_chat(15, ({ "The fly goes: 'Bzzzzzzz'.\n",
		       "The fly spins around in tiny circles wildly.\n" }));
}
