#include "/d/Empire/islands/chaos.h"

inherit CAS_I_CRITTER;

static void
create() 
{
    ::create();
    set_name("Angron");
    set_short("Angron the Chaos Lord of Khorne");
    set_long("Angron is one of the most favoured lords in Khorne's duty. " +
	     "He has seen many a battle, and won them all. He is well " +
	     "known for his skill in combat, and those who live to speak " +
	     "about it are usually those Angron sees unworthy " +
	     "to be killed by him."); 
    set_race("mutant");
    add_id(({ "lord", "mutant", "chaoslord", "angron", "chaos lord",
              "chaos lord of khorne" }));
    set_gender(1);
    set_level(29);
    set_hp(1500);
    set_str(40);
    set_dex(40);
    set_al(-1666);
    set_wc(20);
    set_ac(15); 
    set_aggressivity(80);
    set_wandering_chance(50);
    set_wandering_time(5);
    set_scary(1);
    set_bored_secs(300);

    add_exp(4500000);
    add_tmp_prop("devotion_khorne", 100);
    add_property("no_stun");
    add_eq(resolve_path("amulet"));
    add_eq(resolve_path("armour"));
    add_eq(resolve_path("axe"));
    add_eq(resolve_path("boot"));
    add_eq(resolve_path("cloak"));
    add_eq(resolve_path("glove"));
    add_eq(resolve_path("helmet"));
    add_eq(resolve_path("ring"));
  
    load_chat(10, ({ "*growl", "*snare", 
                     "*emote looks around for a victim." }));
    load_a_chat(10, ({ store_fp("do_grow"),
                       store_fp("do_prot") }));
    add_hook("__fight_beat", store_fp("on_fight_beat"));
    add_hook("__kill", store_fp("on_kill"));
    add_hook("__die", store_fp("on_die"));
}

static void
do_grow(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, bold("\nAngron grows stronger!\n\n"));
    set_str(query_str() + 10);
}

static void
do_prot(object ply, object foe) 
{
    object env;
    string str;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "Angron raises his hand towards the sky, beckoning his " +
              "master for help in the battle. His prayers are granted, " + 
              "and he seems to be filled with a surge of power.\n");
    str = ({ "slash", "blunt", "pierce", "chop", "claw", "bite" })[random(6)];
    add_tmp_prop("prot_" + str, 22);
    heal_self(222);
}

static void
on_fight_beat(object foe) 
{
    object env;
    if (objectp(env = environment())) {
        return;
    }
    if (random(100) < 10) {
        tell_room(env, "The wounds on Angron's body heal themselves.\n");
        heal_self(150);  
    }
    if (random(100) < 2 && query_str() < 100) {
        command("yell WHOEVER MORTAL GETS IN MY WAY NOW WILL "+
                "SURELY PERISH! AAAH, THE STRENGTH THAT KHORNE "+
                "GIVES HIS MOST FAITHFUL!");
        set_str(100);
    }
    if (objectp(foe) && (int)foe->query_hp() < 50) {
        EMP_D_CRITICAL->hit_player(this_object(), foe, 75 + random(25), "head");
    }
}

static void
on_kill(object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    switch(random(4)) {
    case 0:
        command("yell Blood for the god of blood!");
        break;
    case 1:
        command("yell Skulls for the throne of Khorne!");
        break;
    case 2:
        env->tell_nearby("You hear the sound of slaughter to the #d!\n", 5);
        break;
    case 3:
        env->tell_nearby("You hear an evil laugh from the #d!\n", 10);
        break;
    }
}

static void
on_die() 
{
    catch(resolve_path("event")->set_next_time(time() + 24 * 60 * 60));
}
