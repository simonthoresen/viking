#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    object ob;
    ::create();
    set_race("insect");
    set_name("beetle");
    add_long("This beetle is pretty big and black.\n");
    add_id(({ "big beetle", "black beetle" }));
    scale_level(1, 5);
    scale_dex(5, 10);
    scale_ac(5, 10);
    scale_wc(1, 4);
    set_al(0);
    setmin("buzzes in");
    setmout("buzzes");
    add_property("unarmed_damage_type",({ "bite" }));
    add_property("unarmed_weapon_name", "jaws");
    add_property("no_headchop");
    add_skill("resist_slash", 20);
    add_skill("resist_chop", 20);
    add_skill("vuln_blunt", 20);
    add_skill("vuln_fire", 30);
}
