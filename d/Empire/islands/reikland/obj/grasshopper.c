#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("fly");
    set_name("grasshopper");
    add_long("It is lurking around making annoying noises.");
    scale_level(1, 4);
    scale_ac(6, 8);
    scale_wc(4, 6);
    scale_dex(8, 10);
    set_al(0);
    setmin("buzzes in");
    setmout("buzzes");
    add_property("unarmed_damage_type", ({ "bite" }));
    add_property("unarmed_weapon_name", "jaws");
    add_property("no_headchop");
    add_skill("vuln_blunt", 20);
    add_skill("vuln_fire", 30);
    add_skill("resist_slash", 20);
    add_skill("resist_chop", 20);
    load_a_chat(15, ({ "You hear some annoying hi-pitched noise.\n",
		       "*say RIRI-RIRI-RIRI-RIRI-RIRI-RIRI-RIRI-RIRI!!" }));
}
