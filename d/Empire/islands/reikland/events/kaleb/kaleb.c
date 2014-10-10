#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private int _devotion;

static void 
create() 
{
    ::create();
    _devotion = 0;

    set_male();
    set_race("undead");
    set_name("Kaleb");
    set_short("an undead warrior");
    set_long("This is the risen remains of the holy warrior Kaleb. He " +
             "is wearing a torn black tunic with a faded red cross on front " +
             "and back, and a ragged brown mantle.");
    add_id(({ "warrior", "undead warrior", "holy warrior" }));
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
    add_hook("__init", store_fp("attack_evil"));
    add_hook("__fight_beat", store_fp("more_devoted"));
    add_hook("__peace_beat", store_fp("slow_regress"));
    add_hook("__beat_stopped", store_fp("clear_devotion"));
    add_tmp_prop("devotion_good", 60);
    load_chat(5, ({ "*moan", "*sigh", "*emote looks around.",
                    "*say Have you seen any demons nearby?",
                    "*say Have you seen Imhotep?" }));
    load_a_chat(100, ({ store_fp("extra_attack") }));
    EMP_D_WEAPON->add_unique(resolve_path("sword"), 100);
    EMP_D_ARMOUR->add_unique(resolve_path("ring"), 100, "ring");
    EMP_D_ARMOUR->add_unique(resolve_path("amulet"), 100, "amulet");
}

static void
extra_attack(object ply, object foe) 
{
    EMP_D_COMBAT->hit_player(ply, foe, _devotion + random(_devotion * 4), 
			     ({ "slash", "chop", "pierce" })[random(3)]);
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
more_devoted(object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    ++_devotion;
    if (_devotion % 5 == 0) {
        tell_room(env, bold("\nAngelic wings of heavenly light unfold " +
                            "around the warrior.\n"));
    }
}

static void
slow_regress() 
{
    if (_devotion > 0) {
        --_devotion;
    }
    heal_self(66);
}

static void
clear_devotion() 
{
    _devotion = 0;
    heal_self(6666);
}

public void
set_devotion(int val) 
{
    _devotion = val;
}

public int
query_devotion() 
{
    return _devotion;
}
