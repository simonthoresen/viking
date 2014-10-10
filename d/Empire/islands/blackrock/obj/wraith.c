#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string dtype;
    switch (val / 40) {
    case 0:
        set_name("Sword wraith");
        dtype = "slash";
        break;
    case 1:
        set_name("Acid wraith");
        add_property("magic");
        dtype = "acid";
        break;
    case 2:
        set_name("Ice wraith");
        add_property("magic");
        dtype = "cold";
        break;
    }
    set_long("This is an incorporeal creature born of evil and darkness, " +
             "despising light and all living things. It is a sinister, " +
             "spectral figure robed in darkness. It has no visual features, " +
             "except for its glowing red eyes.");
    add_property("unarmed_damage_type", dtype);
    add_property("undead");
    load_a_chat(25 + val / 4, ({ store_fp("cast_soul_drain") }));
    EMP_D_ARMOUR->add_armour(75 + random(val), "helmet");
}

static void
cast_soul_drain(object ply, object foe) 
{
    int val;
    if (!objectp(ply) || 
        !objectp(foe) ||
        (val = foe->query_hp()) <= 0) 
    {
        return;
    }
    tell_object(foe, "\n\n" + query_name() + " reaches out for you..\n");
    foe->reduce_hit_point(10 + random(10));
    val = val - foe->query_hp();
    if (val > 0) {
        MESSAGE_D->weapon_noise(foe, val, "drain", ply);
        ply->reduce_hit_point(-val);
        tell_object(foe, "\n\n");
    }
}
