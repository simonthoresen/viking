#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
create() 
{
    ::create();
    add_id("flayer");
}

static void
init_dangerlevel(int val) 
{
    set_long("It is a humanoid with an octopus-like head. It has four " +
             "tentacles around a lamprey-like mouth. Its eyes are pale " +
             "white.");
    add_property("unarmed_damage_type", "magic");
    add_money(750 + random(10 * val));
    load_a_chat(25 + val / 4, ({ store_fp("cast_mind_drain") }));
    EMP_D_ARMOUR->add_armour(50 + random(val), "amulet");
    EMP_D_WEAPON->add_weapon(50 + random(50), "onehanded");
    EMP_D_WEAPON->add_weapon(50 + random(50), "onehanded");
}

static void
cast_mind_drain(object ply, object foe) 
{
    int val;
    if (!objectp(ply) || 
        !objectp(foe) ||
        (val = foe->query_sp()) <= 0) 
    {
        return;
    }
    command("*emote radiates a mentally exhausting aura.");
    foe->reduce_spell_point(25 + random(25));
    val = val - foe->query_sp();
    if (val > 0) {
        MESSAGE_D->weapon_noise(foe, val, "drain", ply);
        ply->reduce_spell_point(-val);
    }
}
