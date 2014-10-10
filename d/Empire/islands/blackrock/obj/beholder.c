#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    switch (val / 75) {
    case 0:
        add_property("unarmed_damage_type", "magic");
        break;
    case 1:
        set_name("Beholder eye tyrant");
        add_id("tyrant");
        add_property("unarmed_damage_type", "drain");
        break;
    }
    set_long("It resembles a floating orb of flesh with a large mouth, " +
             "single central eye, and lots of smaller eyestalks on top with " +
             "deadly magical powers.");
    add_id("eye");
    add_money(750 + random(10 * val));
    add_property("magic");
    make(BRD_C_COIN)->add_amount(BRD_COIN_LOOT(val));
}
