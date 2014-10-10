#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("buck");
    add_id(({ "buck", "peaceful buck", "mountain buck", "animal" }));
    add_long("You notice how calmly this animal grasses on the few straws " +
             "that is up in the mountains. " +
             "It has got two big, curved horns to defend itself.");
    scale_level(16, 19);
    scale_int(1, 5);
    scale_dex(17, 22);
    scale_str(25, 35);
    scale_wc(20, 30);
    scale_ac(7, 11);
    scale_hp(350, 425);
    set_al(random(400) - 200);
    add_property("unarmed_weapon_name", "horns");
    add_property("unarmed_damage_type",
                 ({ "blunt", "blunt", "bite", "pierce", "Impact" }));
    add_skill("resist_blunt", 60);
    add_skill("resist_slash", 50);
    add_skill("resist_chop", 40);
    add_skill("resist_cold", 40);
    add_skill("prot_blunt", 10);
    add_skill("prot_chop", 5);
    add_skill("prot_slash", 5);
    add_skill("vuln_pierce", 40);
    add_skill("vuln_fire", 10);
    load_chat(5, ({ "Buck grasses some.\n",
                    "The buck looks at you innocently.\n",
		    "You tremble in fear gazing at those mighty horns on " +
                    "the buck.\n" }));
    load_a_chat(40, ({ "The buck rams its horns into the opponent.\n",
                       "Buck kicks up some dust with its hoves.\n",
		       "Buck snorts angrily.\n" }));
    add_hook("__damage_dealt", store_fp("maybe_throw"));
}

static void
maybe_throw(int dmg, string type, object foe, string loc) 
{
    object env;
    if (!objectp(foe) || !objectp(env = environment(foe)) ||
        dmg < 15 || random(100) > 10) 
    {
        return;
    } 
    tell_object(foe, "The buck rams into you!\n");
    tell_room(env, "The buck rams into " + foe->query_name() + 
              ".\n", ({ foe }));
    EMP_D_COMBAT->throw_player(foe, 1);
}
