#include "/d/Empire/islands/reikland.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_male();
    set_race("undead");
    set_name("Kalis Pathon");
    set_short("an undead magician");
    set_long("This is the risen remains of the holy magician Kalis Pathon. " +
             "He is wearing a torn black tunic with a faded red cross on " +
             "front and back, and a ragged brown mantle.");
    add_id(({ "magician", "undead magician", "monk magician", "monk",
              "kalis", "pathon" }));
    set_level(29);
    set_str(50);
    set_dex(10);
    set_hp(2222);
    set_al(ALIGN_SAINTLY);
    set_scary(1);
    set_bored_secs(300);
    add_property("undead");
    add_skill("resist_fire", 50);
    add_skill("resist_cold", 50);
    add_skill("resist_electricity", 50);
    add_skill("resist_acid", 50);
    add_skill("resist_magic", 50);
    add_skill("prot_drain", 100);
    add_tmp_prop("devotion_good", 40);
    add_hook("__init", store_fp("attack_evil"));
    load_chat(5, ({ "*moan", "*sigh", "*emote looks around.",
                    "*say Have you seen any demons nearby?",
                    "*say Have you seen Imhotep?" }));
    load_a_chat(50, ({ store_fp("judge_good"),
                       store_fp("burn_evil"),
                       store_fp("drain_life") }));
    EMP_D_WEAPON->add_unique(resolve_path("staff"), 100, "onehanded");
	EMP_D_WEAPON->add_unique(resolve_path("book"), 100, "onehanded");
 
}

static void
attack_evil() 
{
    object ply;
    if (!objectp(ply = this_player()) ||
        ply->query_alignment() > ALIGN_EVIL ||
        ply->query_invis()) 
    {
        return;
    }
    do_attack(ply);
}

static void
drain_life(object ply, object foe) 
{
    int val;
    if (!objectp(foe)) {
        return;
    }
    tell_room(environment(), 
              bold("\n\nA ray of heavenly light falls upon the magician.\n"));
    EMP_D_COMBAT->hit_player(ply, foe, foe->query_max_hp() / 5, "magic");
}

static void
judge_good(object ply, object foe) 
{
    if (!objectp(foe) || 
        foe->query_alignment() < ALIGN_GOOD)
    {
        return;
    }
    command("say YOUR MORALE IS A LIE!");
    tell_object(foe, "You feel something change inside you.\n");
    foe->add_alignemnt(-100);
}

static void
burn_evil(object ply, object foe) 
{
    if (!objectp(foe) ||
        foe->query_alignment() > ALIGN_EVIL) 
    {
        return;
    }
    command("say I CONDEMN YOU TO BURN IN HEAVEN'S FIRE!");
    EMP_D_COMBAT->hit_player(ply, foe, 33 + random(33), "fire");
}
