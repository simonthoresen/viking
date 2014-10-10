#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_race("rabbit");
    set_name("rabbit");
    add_long("This fellow is curious and very annoying.");
    add_id(({ "annoying rabbit", "curious rabbit" }));
    scale_level(2, 8);
    scale_str(3, 5);
    scale_dex(8, 14);
    scale_hp(60, 100);
    set_al(-65 + random(70));
    set_aggressivity(1);
    setmin("jumps in");
    setmout("jumps");
    add_property("unarmed_weapon_name", "teeth");
    add_property("unarmed_damage_type",
                 ({ "blunt", "blunt", "bite", "bite", "bite" }));
    load_chat(10, ({ "*emote jumps back and forth.",
                     "*jump tea",
                     "*look mock" }));
    load_a_chat(40, ({ "*gobble",
                       "*shiver fea",
                       "*sniff" }));
}
