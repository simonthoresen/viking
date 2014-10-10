#include "/d/Empire/islands/altdorf.h"
 
inherit ALT_I_CITIZEN;
 
static void
create() 
{
    object this;
    ::create();
    set_name("Reidar");
    set_short("Captain Reidar of the Altdorf Guard");
    set_long("Reidar has devoted his life in the serve of the cityguards, " +
             "he looks incredibly strong, and you can see that this is no " +
             "easy kill. He has the signia of Freyr on his forehead.");
    add_id(({ "knight", "guard", "captain"}));
    set_gender(1);
    set_level(29);
    set_hp(5000);
    add_money(1000 + random(3000));
    add_exp(1250000);
    set_al(1000 + random(600));
    set_race("human");
    set_faction("good");
    set_ac(20); 
    set_str(45);
    set_dex(45);
    set_greeting("\n%^BOLD%^Reidar looks ALOT stronger than " +
                 "before!%^END%^\n\n");
    load_chat(5, ({ "*say Help us drive off the forces of evil from these " +
                    "lands and you will be rewarded.",
                    "*flex",
                    "*emote swears: I can't wait until I get my hands on " +
                    "the bastard that has been stealing and looting in the " +
                    "village lately.",
		    "*say I handle all bounty-hunting in the Empire.",
		    "*say If you need something to do, maybe I can help you.",
		    "*emote looks around for intruders.",
		    "*emote sighs: I hope the chaos attacks will stop soon."}));
    load_a_chat(25, ({ store_fp("do_fury"), 
                       store_fp("do_throw"),
                       store_fp("do_wound") }));
    add_hook("__bnotify_attack", store_fp("on_notify"));
    add_hook("__die", store_fp("on_die"));

    if (!clonep(this = this_object())) {
        return;
    }
    add_eq(ALT_DIR_OBJ + "buckler");
    EMP_D_ARMOUR->add_armour(150);
    EMP_D_WEAPON->add_weapon(125);
    EMP_D_CONTAINER->add_container(125);
}

static void
do_fury(object ply, object foe) 
{
    int i, len;
    object env, obj;
    if (!objectp(foe) || !objectp(env = environment()) ||
        !objectp(obj = query_weapon(1))) {
        return;
    }
    tell_room(env, bold("Reidar's attacks become a blur!\n"));
    for (i = 0, len = 5 + random(5); i < len; ++i) {
        if (!objectp(foe) || !objectp(obj)) {
            break;
        }
        hit_with_weapon(obj, foe, i * 5);
    }
}

static void
do_throw(object ply, object foe) 
{
    object env;
    if (!objectp(foe) || !objectp(env = environment()) ||
        !objectp(query_worn_armour("shield"))) 
    {
        return;
    }
    tell_room(env, "Reidar THROWS himself forward with his shield!\n");
    if (EMP_D_COMBAT->hit_player(ply, foe, 50 + random(50),
                                 "impact") < 50) 
    {
        return;
    }
    if (!EMP_D_COMBAT->throw_player(foe, 1)) {
        EMP_D_COMBAT->stun_player(foe, 1, ply);
    }
}

static void
do_wound(object ply, object foe) 
{
    object env;
    if (!objectp(foe) || !objectp(env = environment()) ||
        !objectp(query_weapon(1))) {
        return;
    }
    tell_room(env, "Reidar JUMPS into the air with his weapon raised!\n");
    if (EMP_D_COMBAT->hit_player(ply, foe, 50 + random(50), "slash") < 50) {
        return;
    }
    EMP_D_COMBAT->wound_player(ply, foe, 50 + random(50));
}

static void
on_notify(object foe) 
{
    object env;
    if (!objectp(foe) || !interactive(foe) || 
        !objectp(env = environment()) ||
        ALT_D_BOUNTY->query_bounty(foe) > 0) 
    {
        return;
    }
    command("say There will be a bounty on your head!");
    ALT_D_BOUNTY->add_bounty(foe, 500 + random(500));
}

static void
on_die(object corpse, object killer) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "As Reidar dies, his soul fades away. You think you " +
              "see an angel leaving.\n");
    ALT_D_BOUNTY->add_bounty(killer, 5000 + random(5000));
}
