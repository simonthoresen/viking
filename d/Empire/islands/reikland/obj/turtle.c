#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("turtle");
    set_name("turtle");
    scale_level(5, 13);
    scale_str(8, 16);
    scale_dex(2, 6);
    set_al(random(500));
    setmin("enters");
    setmout("leaves slowly");
    add_property("unarmed_weapon_name", "mouth");
    add_property("unarmed_damage_type",
                 ({ "blunt", "bite", "bite", "bite" }));
    add_skill("swimming", 100);
    load_chat(10, ({ "*emote walks very slowly.",
                     "*emote eats some grass.",
                     "*emote looks pretty old.",
                     "*emote is slowly." }));
    load_a_chat(40, ({ "*emote hides in its shell.",
                       "*emote snaps at you!",
                       "*emote covers into its home." }));
}
