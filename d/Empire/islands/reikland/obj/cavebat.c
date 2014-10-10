#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("bat");
    set_name("cavebat");
    add_id(({ "bat", "flying bat", "shadow", "creature" }));
    add_long("As you look at this creature, you notice two long blood-" +
             "stained fangs residing on the face resembling to a daemon's. " +
             "The bat seems to look straight back at you with its red " +
             "gleaming eyes, making you tremble with fear.");
    scale_level(12, 18);
    scale_wc(5, 15);
    scale_ac(2, 8);
    scale_hp(200, 400);
    set_al(-400 - random(700));
    set_aggressivity(70);
    setmin("flaps in");
    setmout("flaps");
    add_skill("resist_pierce", 90);
    add_skill("resist_blunt", 50);
    add_skill("resist_slash", 40);
    add_skill("resist_chop", 30);
    add_skill("resist_cold", 20);
    add_skill("prot_pierce", 30);
    add_skill("prot_blunt", 15);
    add_skill("prot_slash", 10);
    add_skill("vuln_fire", 20);
    add_property("unarmed_damage_type",({ "claw", "bite" }));
    add_property("unarmed_weapon_name", "claws");
    add_property("no_headchop");
    load_chat(5, ({ "You hear the flapping of some wings nearby.\n",
                    "You feel watched.\n",
		    "You spot a shadow flying by.\n" }));
    load_a_chat(40, ({ "You hear some wild hi-pic screams from a bat.\n",
                       "The bat hisses at you menacingly.\n",
                       "While flying the bat seems less affected by the " +
                       "attacks.\n" }));
}
