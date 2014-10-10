#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    object obj;
    ::create();
    set_name("Fenrir");
    set_short("the MONSTROUS Fenrir wolf");
    set_long("A VERY large wolf with raven black fur and tremendously large " +
             "teeth. It is wearing a spiked metal collar with the remains " +
             "of a broken chain attached to it. It must have torn free from " +
             "somewhere..");
    add_id(({ "wolf", "monstrous wolf", "fenrir wolf", "monstrous fenrir" }));
    set_level(29);
    set_al(-999);
    set_wc(66);
    set_ac(10);
    set_hp(2500);
    set_aggressive(1);
    set_scary(1);
    set_bored_secs(300);
    add_property("unarmed_damage_type", ({ "claw", "claw", "bite" }));
    load_a_chat(100, ({ store_fp("attack") }));
    add_hook("__damage_dealt", store_fp("on_damage_dealt"));
    add_hook("__die", store_fp("on_die"));

    obj = new(EMP_C_BLOOD);
    obj->add_blood(666);
    obj->move(this_object());
}

static void 
on_damage_dealt(int dmg, string dtype, object foe, 
                string loc, object weapon) 
{
    object ply, env;
    if (!objectp(ply = previous_object()) ||
        !objectp(env = environment(ply)) ||
        !objectp(foe) || !objectp(present(foe, env)) ||
        dmg < 15) 
    {
        return;
    }
    if (dmg > 100 && EMP_D_LIMB->has_limb("right hand", foe)) {
        message("hityou", "FENRIR BITES DOWN ON YOUR RIGHT HAND!\n", foe);
        tell_room(env, "Fenrir bites down on " + foe->query_name() + 
                  "'s right hand.\n", ({ foe }));
        EMP_D_LIMB->cut_limb(foe, "right hand");
    }
    EMP_D_COMBAT->wound_player(ply, foe, dmg);
}

static void
on_die(object corpse, object foe) 
{
    if (objectp(corpse)) {
        object obj;
        if (objectp(obj = D_TREASURE->get_unique(resolve_path("rclaw"))) ||
            objectp(obj = D_TREASURE->get_unique(resolve_path("lclaw"))) || 
            objectp(obj = D_TREASURE->get_unique(resolve_path("cloak")))) 
        {
            obj->move(corpse);
        }
    }
    if (objectp(foe)) {
	EMP_D_ACHIEVEMENT->unlock(foe, "fenrir_wolf");
    }
}
