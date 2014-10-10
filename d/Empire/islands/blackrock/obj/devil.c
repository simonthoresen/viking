#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    int idx;
    string mtype, dtype;
    idx   = val / 30;
    mtype = ({ "barbed", "bone", "horned", "ice" })[idx];
    dtype = ({ "claw", "blunt", "pierce", "cold" })[idx];
    set_name(capitalize(mtype) + " devil");
    set_long("A tall, emaciated being with dried skin stretched so tight as " +
             "to outline and emphasize every bone. It has a skull-like head " +
             "and a bony tail like a scorpion's, and exude a stench of " +
             "decay.");
    add_tmp_str(val / 10);
    add_property("unarmed_damage_type", dtype);
    add_property("magic");
    EMP_D_ARMOUR->add_armour(75 + random(val), "cloak");
}
