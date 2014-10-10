#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("rat");
    set_name("rodent");
    add_long("It is searching for scraps of food.");
    scale_level(2, 5);
    scale_dex(7, 10);
    scale_hp(30, 70);
    set_al(-89 + random(100));
    set_aggressivity(5);
    setmin("paces in");
    setmout("paces");
    add_property("unarmed_weapon_name", "teeth");
    add_property("unarmed_damage_type", ({ "bite" }));
    load_chat(10, ({ "*emote paces back and forth.",
                     "*emote munches on some food.",
                     "*emote squeeks." }));
    load_a_chat(40, ({ "*emote squeeks!",
                       "*hide",
                       "*emote stands up on its small legs." }));
}
