#include "/d/Empire/islands/reikland.h"

inherit RED_DIR_EVENTS + "imhotep/demon_base";

private object _portal;

static void
create()
{
    ::create();
    _portal = make(parse_path("portal"));

    set_name("Imhotep");
    set_short("a gruesome demon lord");
    set_long("This is a foul creature of evil. The face of this being is a " +
             "grotesque picture of mankind's worst nightmare, a hellish " +
             "portrait of the underworld. Imhotep can most surely lay any " +
             "world waste and destroy any opponent stupid enough to attack " +
             "or stand in its way.\n");
    add_id(({ "lord", "demon lord" }));
    set_level(29);
    set_hp(30000);
    set_sp(1500);
    set_al(-2000);
    set_str(100);
    set_dex(50);
    set_wc(75);
    set_ac(20);
    set_wandering_chance(80);
    set_wandering_time(10);
    add_property(({ "no_disarm", "no_behead", "no_possess", "no_stun" }));
    add_property("unarmed_damage_type","claw");
    add_hook("__destroy", store_fp("close_portal"));
    add_hook("__die", store_fp("reward_kill"));
    set_combat_arr(({
        1, "", "misses", 0,
        3, " in the stomach", "tickles", 0,
        5, " a little", "bruises", 0,
        7, "", "scratches", 0,
        9, "", "grazes", 0,
        11, "", "nicks", 0,
        13, "", "scars", 0,
        15, " hard", "hits", 0,
        20, " badly", "injures", 0,
        30, " drawing blood", "wounds", 0,
        40, " with a bonecrushing sound", "mauls", 0,
        50, " horribly", "maims", 0,
        60, " terribly", "mangles", 0,
        70, " totally", "mars", 0,
        80, " beyond recognition", "LACERATES", 0,
        90, "", "DECIMATES", 0,
        100, "", "DEVASTATES", 0,
        110, "", "ERADICATES", 0,
        120, "", "OBLITERATES", 0,
        130, "", "EXTIRPATES", 0,
        140, " boiling blood and burning organs", "INCINERATES", 0,
        150, " totally", "MUTILATES", 0,
        160, " into a pulp of blood", "DISEMBOWELS", 0,
        170, " beyond human aid", "MASSACRES", 0
    }));
    load_a_chat(35, ({
        store_fp("cast_blast"),
        store_fp("cast_bolt"),
        store_fp("cast_ball"),
        store_fp("cast_storm"),
        store_fp("cast_frenzy"),
        store_fp("cast_inferno"),
        store_fp("cast_gate"),
        store_fp("cast_regen")
    }));
    EMP_D_WEAPON->add_unique(parse_path("sword"), 150);
    EMP_D_WEAPON->add_unique(parse_path("scythe"), 150);
    EMP_D_ARMOUR->add_unique(parse_path("amulet"), 125);
    EMP_D_ARMOUR->add_unique(parse_path("helmet"), 150);
}

static void
close_portal()
{
    if (!objectp(_portal)) {
        return;
    }
    _portal->destroy(1);
}

static void
reward_kill(object corpse, object foe)
{
    object env;
    if (!objectp(foe) ||
        !objectp(env = environment()))
    {
        return;
    }
    tell_room(env, "\n\n\nImhotep EXPLODES in an orgy of blood and gore!!\n");
    EMP_D_COMBAT->spray_blood(env, 666, this_object());
    EMP_D_ACHIEVEMENT->unlock(foe, "imhotep");
    tell_room(env, "A ray of heavenly light falls upon " +
              foe->query_name() + ".\n");
    tell_object(foe, "A ray of heavenly light falls upon you, filling you " +
                "with divine power!\n");
    foe->set_modifier("imhotep:str", "str", "magic", 3);
    foe->set_modifier("imhotep:dex", "dex", "magic", 3);
    foe->set_modifier("imhotep:con", "con", "magic", 3);
    foe->set_modifier("imhotep:int", "int", "magic", 3);
}

private string
random_type()
{
    return ({ "fire", "cold", "electricity", "impact",
              "drain", "acid", "magic" })[random(7)];
}

static void
cast_blast(object ply, object foe)
{
    tell_room(environment(ply), "%^B_MAGENTA%^%^L_YELLOW%^Imhotep casts a " +
              "chaos-blast!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 30 + random(30),
                             random_type(), 0, "spell");
}

static void
cast_bolt(object ply, object foe)
{
    tell_room(environment(ply), "%^B_MAGENTA%^%^L_YELLOW%^Imhotep casts a " +
              "chaos-bolt!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 20 + random(20),
                             random_type(), 0, "spell");
}

static void
cast_ball(object ply, object foe)
{
    tell_room(environment(ply), "%^B_MAGENTA%^%^L_YELLOW%^IMHOTEP CASTS A " +
              "CHAOS-BALL!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 20 + random(20),
                             capitalize(random_type()), 0, "spell");
}

static void
cast_storm(object ply, object foe)
{
    tell_room(environment(ply), "%^B_BLUE%^Imhotep calls forth a " +
              "lightning-storm!%^END%^\n");
    EMP_D_COMBAT->hit_players(ply, ply->query_attackers(), 45 + random(45),
                              "electricity", 0, "spell");
}

static void
cast_frenzy(object ply, object foe)
{
    int i, len;
    tell_room(environment(ply), bold("\n\nImhotep goes into a mad frenzy!\n"));
    for (i = 0, len = 2 + random(4); i < len; ++i) {
        attack();
    }
}

static void
cast_inferno(object ply, object foe)
{
    object *arr, env;
    int i, len;
    if (!objectp(ply) ||
        !objectp(env = environment(ply)) ||
        !arrayp(arr = ply->query_attackers()))
    {
	return;
    }
    tell_room(env, "%^B_RED%^%^L_YELLOW%^Imhotep calls forth an inferno of " +
              "fire!%^END%^\n");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        object obj;
        if (!objectp(foe = arr[i]) ||
            EMP_D_COMBAT->hit_player(ply, foe, 20 + random(20), "fire",
                                     0, "spell") < 5)
        {
            continue;
        }
        if (!objectp(foe) || foe->query_dead()) {
            continue;
        }
        obj = new(parse_path("fire"));
        obj->set_caster(ply);
        obj->move(foe);
    }
}

static void
cast_gate(object ply, object foe)
{
    command("yell COME TO MY AID, CHILDREN!");
    make(parse_path("demon"), environment(ply))->do_attack(foe);
}

static void
cast_regen(object ply, object foe)
{
    tell_room(environment(ply), "Imhotep's wounds mend.\n");
    ply->heal_self(125 + random(125));
}
