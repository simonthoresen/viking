#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("fly");
    set_name("butterfly");
    add_id(({ "butterfly", "colourful butterfly", 
              "beautiful butterfly", "small butterfly" }));
    add_long(({ "The butterfly is very beautiful to look at.",
                "This butterfly is pretty small.",
                "This butterfly is gorgeous.",
                "This butterfly looks very nice." })[random(4)]);
    scale_level(1, 3);
    scale_wc(1, 3);
    scale_dex(8, 10);
    set_ac(0);
    set_al(300);
    setmin("flaps in");
    setmout("flaps");
    add_property("unarmed_damage_type",({ "blunt" }));
    add_property("no_headchop");
    add_property("flying");
    add_skill("resist_pierce", 100);
    add_skill("resist_slash", 20);
    add_skill("resist_chop", 20);
    add_skill("vuln_fire", 30);
    load_a_chat(15, ({ "The butterfly flaps frantically with its wings.\n",
		       "The butterfly looks stunningly beautiful!\n" }));
}
