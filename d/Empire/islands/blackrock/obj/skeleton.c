#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string type;
    type = ({ "lion", "bear", "drake" })[val / 40];
    set_name("Skeletal " + type);
    set_long("It is a reanimated skeleton of " + add_article(type) + ". It " +
             "has a pair of glowing red eyes and razor-sharp claws.");
    add_id(type);
    add_property("unarmed_damage_type", "claw");
    add_property("undead");
    add_skill("prot_pierce", 100);
    make(BRD_C_COIN)->add_amount(BRD_COIN_LOOT(val));
}
