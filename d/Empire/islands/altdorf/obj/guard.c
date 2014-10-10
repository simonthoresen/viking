#include "/d/Empire/islands/altdorf.h"

#define PEACE_WANDER   30
#define CRIME_WANDER    2
#define CRIME_TIME     30

inherit ALT_I_CITIZEN;

static void
create() 
{
    object this;
    string name;
    ::create();
    set_gender(random(5) ? 1 : 2);
    if (query_male()) {
	set_name(ALT_D_NAME->query_male_name());
    } else {
	set_name(ALT_D_NAME->query_female_name());
    }
    name = ALT_D_NAME->query_last_name();
    add_id(({ name, lower_case(name) }));
    set_name(query_name() + " " + name);
    set_short(query_name() + " of the Altdorf Guard");
    set_long("This is one of the fine soldiers serving under the throne " +
             "with much loyalty and dedication. " + query_pronoun() + " is " +
             "well-built and resilient.");
    add_id(({ "cityguard", "guard", "guardsman", "cityguard of altdorf" }));
    set_faction("good");
    set_level(23 + random(5));
    set_str(25 + random(5));
    set_dex(23 + random(3));
    set_int(20);
    set_con(24 + random(4));
    set_hp(600 + random(300));
    add_money(200 + random(500));
    add_exp(2000 * 50);
    set_al(-50 + random(700) + random(1000));
    set_wandering_time(PEACE_WANDER);
    set_wandering_chance(80);
    set_wc(10);
    set_ac(15);
    add_skill("resist_slash",20);
    add_skill("resist_chop",20);
    add_skill("resist_bite",20);
    add_skill("resist_claw",15);
    add_skill("resist_blunt",30);
    add_skill("resist_fire",10);
    add_skill("resist_cold",10);
    load_chat(5, ({ "*say Y'all behave now.",
                    "*sigh",
		    "*say Kids...",
		    "*lick",
		    "*yawn",
		    "*say Sometimes I wish something exciting could happen...",
		    "*bite",
		    "*say These damn chaos beasts get on our nerves.",
		    "*bored",
		    "*sneeze",
                    "*sniff" }));  
    load_a_chat(10, ({ "*say I knew you couldn't be trusted!",
                       "*say You had that look about you...",
                       "*say Well, surrender NOW!",
                       "*yell Do not resist!",
                       "*say You are under arrest.",
                       "*yell Guardsmen!",
                       store_fp("attack") }));
    if (!clonep(this = this_object())) {
        return;
    }
    EMP_D_WEAPON->add_weapon(75);
    EMP_D_ARMOUR->add_armour(50);
    EMP_D_ARMOUR->add_armour(50);
    EMP_D_ARMOUR->add_armour(50);
    add_hook("__wander_done", store_fp("calm_down"));
    add_hook("__init", store_fp("check_reward"));
    add_hook("__kill", store_fp("claim_reward"));
}

public void
notify_attack(object ply, object foe, int row, int col) 
{
    if (query_property("guardian") || 
        !objectp(ply) || 
        !objectp(foe) ||
        !set_goal(row, col))
    {
	return;
    }
    command("yell I am coming, " + ply->query_name() + "!");
    set_wandering_time(CRIME_WANDER);
}

static void
calm_down() 
{
    set_wandering_time(PEACE_WANDER);
}

static void
check_reward() 
{
    object ply;
    if (!objectp(ply = this_player()) || ply->query_invis() ||
        ALT_D_BOUNTY->query_reward(ply) <= 0) 
    {
        return;
    }
    command("say There is a bounty on your head, " + ply->query_name() + "!");
    do_attack(ply);
}

static void
claim_reward(object victim, object killer) 
{
    int val;    
    if (!objectp(victim) || (val = ALT_D_BOUNTY->query_reward(victim)) <= 0) {
        return;
    }
    command("say That was the easiest " + val + " coins I ever made!");
    ALT_D_BOUNTY->set_reward(victim, 0);
}

public int
is_guard() 
{
    return 1;
}
