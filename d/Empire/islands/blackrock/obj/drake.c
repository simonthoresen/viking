#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string mtype, dtype;
    int idx;
    idx   = val / 40;
    mtype = ({ "rage", "bloodseeker", "spitting" })[idx];
    dtype = ({ "claw", "bite", "acid" })[idx];
    set_name(capitalize(mtype) + " drake");
    set_long("This is a large lizard-like creature with four limbs. It has a " +
             "low-slung body, much like a crocodiles, with its belly lying " +
             "across the ground.");
    add_property("unarmed_damage_type", dtype);
    make(BRD_C_COIN)->add_amount(BRD_COIN_LOOT(val));
}
