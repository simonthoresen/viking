#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string mtype, dtype;
    int idx;
    idx   = val / 17;
    mtype = ({ "air", "earth", "fire", "water", "ooze", "light" })[idx];
    dtype = ({ "magic", "impact", "fire", "cold", "acid", 
               "electricity" })[idx]; 
    set_name(capitalize(mtype) + " elemental");
    set_long("It resembles a ferocious bear, but made completely of " + 
             mtype + ".");
    add_skill("prot_" + dtype, 100);
    add_property("unarmed_damage_type", dtype);
    add_property(({ "no_crit", "no_stun" }));
    make(BRD_C_COIN)->add_amount(BRD_COIN_LOOT(val));
}
