#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string *dtype;
    switch (val / 26) {
    case 0:
        set_name("Flesh golem");
        set_long("A misshapen brutes with taut flesh on which visages press " +
                 "out from beneath as though trapped within. Its face is a " +
                 "gaping orifice from which howls of pain issue.");
        dtype = ({ "bite", "claw" });
        break;
    case 1:
        set_name("Clockwork golem");
        set_long("A clockwork giant that grinds and ratchets implacably " +
                 "towards you, grabbing at you to grind and crush you with " +
                 "its gears.");
        load_a_chat(20, ({ "*say TICK TOCK TICK TOCK TICK TOCK!" }));
        dtype = ({ "blunt", "claw", "impact" });
        break;
    case 2:
        set_name("Tombstone golem");
        set_long("A powerful guardians constructed from grave headstones. " +
                 "It is able to slay living beings with the negative energy " +
                 "that empowers it through their powerful strike.");
        add_property("magic");
        dtype = ({ "impact", "magic", "drain" });
        break;
    case 3:
        set_name("Ironwyrm golem");
        set_long("An animated, self-contained furnace built into the shape " +
                 "of a dragon. Smoke trails from its nostrils, and it " +
                 "exudes a palpable heat.");
        add_property("magic");
        dtype = ({ "bite", "claw", "fire", "Fire" });
        break;
    }
    add_tmp_con(11);
    add_property("unarmed_damage_type", dtype);
    EMP_D_ARMOUR->add_armour(75 + random(val), "armour");
}
