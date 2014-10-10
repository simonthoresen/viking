#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("rat");
    set_name("rat");
    add_long("It looks ordinary.");
    scale_level(2, 4);
    scale_dex(5, 9);
    set_al(-50 + random(150));
    set_aggressivity(5);
    setmin("paces in");
    setmout("paces");
    load_chat(10, ({ "*emote paces back and forth.",
                     "*emote munches on some food.",
                     "*emote squeeks." }));
    load_a_chat(40, ({ "*emote squeeks!",
                       "*hide",
                       "*emote stands up on its small legs." }));
}
