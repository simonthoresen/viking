#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string mtype, dtype;
    int idx;
    idx   = val / 30;
    mtype = ({ "Wilt-eye", "Mesmeric-eye", "Venom-eye", "Abyssal" })[idx];
    dtype = ({ "bite", "magic", "acid", "drain" })[idx]; 
    set_name(mtype + " basilisk");
    set_long("It is a large lizard with high finlike crests down its head, " +
             "back and tail. It has a brown to olive skin, and a yellow " +
             "stripe on its upper lip, and along either side of its body.");
    add_id("lizard");
    add_skill("resist_" + dtype, 100);
    add_property("unarmed_damage_type", dtype);
    add_property("magic");
    load_a_chat(25, ({ store_fp("do_stare") }));
    make(BRD_C_COIN)->add_amount(BRD_COIN_LOOT(val));
}

static void
do_stare(object ply, object foe) 
{
    command("stare " + D_MAINSOUL->query_adverb_random() + " " + 
            foe->query_real_name());
}
