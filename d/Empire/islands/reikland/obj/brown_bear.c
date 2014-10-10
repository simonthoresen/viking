#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

private int _grizzly;

static void
create() 
{
    ::create();
    _grizzly = 0;

    set_race("bear");
    set_name("brown bear");
    add_long("This is the kind of bear you do not want to be messing around " +
             "with. It looks rather peaceful now, though.");
    scale_level(15, 20);
    scale_str(26, 31);
    scale_dex(26, 31);
    scale_hp(200, 300);
    scale_wc(7, 17);
    scale_ac(10, 20);
    set_al(random(100)-50);
    set_aggressivity(1);
    setmin("crawls in");
    setmout("crawls");
    add_skill("resist_cold", 70);
    add_skill("resist_blunt", 60);
    add_skill("resist_slash", 50);
    add_skill("resist_pierce", 10);
    add_skill("prot_cold", 10);
    add_skill("vuln_chop", 30);
    add_skill("vuln_fire", 70);
    add_property("unarmed_damage_type", ({ "bite", "claw" }));
    add_property("unarmed_weapon_name", "jaws");
    add_hook("__damage_done", store_fp("become_grizzly"));
    add_hook("__die", store_fp("noisy_death"));
    add_hook("__kill", store_fp("eat_corpse"));
    set_combat_arr(({  1, "", "missed", 0, 
                       5, " with its bloody claws", "grazed", 0,
                      10, " making small wounds", "bites", 0,
                      20, " down", "knocks", 0, 
                      30, " drawing blood", "bites", 0, 
                      50, " making terrible scars and blood gush all over", 
                          "clawed",0 ,
                      80, " with a bonecrushing sounds, breaking several ribs", 
                          "smashed", 0 }));
    load_chat(7, ({ "*emote munches on some berries.",
                    "*emote sniffs the air.",
                    "*emote eyes you suspiciously." }));
    load_a_chat(15, ({ "*growl men", 
                       "*emote roars and frightens you almost to death.",
                       "*emote bares its teeth." }));
}

static void
become_grizzly(int dmg, string type, object foe, string loc) 
{
    object env;
    if (_grizzly || dmg <= 0 || random(100) > 10 || 
        !objectp(env = environment())) 
    {
        return;
    }
    _grizzly = 1;
    tell_room(env, "Suddenly the brownbear makes a giant roar as it tastes " +
              "its own blood. Now its hunger for blood is awaken. You back " +
              "away uneasily as the grizzly bear goes completely berserk " +
              "and attacks everyone!\n");

    set_name("grizzly bear");
    add_long("It looks really pissed off.");
    scale_level(20, 29);
    scale_str(31, 40);
    scale_dex(31, 40);
    scale_hp(400, 600);
    scale_wc(50, 60);
    scale_ac(10, 20);
    set_al(100 - random(800));
    set_aggressivity(90);
    load_chat(10, ({ "*emote licks its wounds.",
                     "*emote groans painfully.",
                     "*emote leaves a trace of blood behind it." }));
    load_a_chat(30, ({ "*growl vic",
                       "*roar men",
                       "*emote bares its teeth." }));
}

static void
eat_corpse(object victim, object killer) 
{
    object env;
    if (!_grizzly ||
        !objectp(env = environment(victim)) ||
        !objectp(present(killer, env))) 
    {
        return;
    }
    tell_room(env, query_name() + " feeds on the flesh of " + 
              victim->query_name() + "!\n");
    reduce_hit_point(victim->query_con() * 5);
}

static void
noisy_death(object corpse, object killer) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "As the bear dies, it groans loudly and then falls to " +
              "the ground with a loud *THUMP!*.\n");
}
