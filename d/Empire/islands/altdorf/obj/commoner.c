#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN;

private string
query_adverb() 
{
    switch (random(24)) {
    case 0:  return "beggar";
    case 1:  return "busy";
    case 2:  return "greedy";
    case 3:  return "handsome";
    case 4:  return "outstanding";
    case 5:  return "poor";
    case 6:  return "proud";
    case 7:  return "sick";
    case 8:  return "strong";
    case 9:  return "ugly";
    case 10: return "weak";
    case 11: return "wounded";
    default: return 0;
    }
}

private string
query_noun() 
{
    if (query_level() < 10) {
	if (query_male()) {
	    return "boy";
	} else {
	    return "girl";
	}
    } else {
	if (query_male()) {
	    return "man";
	} else {
	    return "woman";
	}
    }
}

static void
create() 
{
    string adverb, noun;
    ::create();
    if (query_male()) { 
	set_name(ALT_D_NAME->query_male_name());
    } else {
	set_name(ALT_D_NAME->query_female_name());
    }
    set_level(5 + random(20));
    if (query_level() > 10) {
        string name;
        name = ALT_D_NAME->query_last_name();
        set_name(query_name() + " " + name);
        add_id(({ name, lower_case(name) }));
    }
    set_ac(2 + random(5));
    set_wc(10 + random(10));
    set_hp(query_hp() + random(query_hp()));
    set_wandering_time(30);
    set_wandering_chance(75);
    add_exp(100000);
    add_property("unarmed_damage_type", ({ "blunt", "blunt", "claw", "bite" }));
    set_faction("good"); 

    noun = query_noun();
    add_id(noun);

    adverb = query_adverb();
    if (stringp(adverb)) {
	add_id(adverb + " " + noun);
    }

    set_short(add_article((stringp(adverb) ? adverb + " " : "") + noun) + 
	      " called " + query_name());
    call_other(this_object(), "setup_" + (stringp(adverb) ? adverb : noun));
}

static void
setup_boy() 
{
    set_long("A small boy playing.");
    load_chat(5, ({ "The boy giggles.\n",
		    "The boy plays on the ground.\n",
		    "The boy looks up at you.\n" }));
    load_a_chat(20, ({ "The boy screams: Are you crazy?\n",
		       "The boy cries.\n",
   		       "The boy pleads.\n",
		       "The boy shouts for help.\n" }));
    setmin("runs in");
    setmout("runs");
}

static void
setup_girl() 
{
    set_long("A small girl fooling around.");
    load_chat(5, ({ "The girl giggles.\n",
		    "The girl plays on the ground.\n",
		    "The girl fools around with a boy.\n",
		    "The girl looks up at you.\n" }));
    load_a_chat(20, ({ "The girl begins to cry.\n",
		       "The girl whines.\n",
		       "The girl shrieks.\n" }));
    setmin("runs in");
    setmout("runs");
}

static void
setup_man() 
{
    set_long("An unimportant citizen of Altdorf, minding his own business.");
    load_a_chat(20, ({ "*yell HELP, HELP!", "*yell HEEEEEELP!!" }));
    add_money(random(500));
}

static void
setup_woman() 
{
    set_long("An unimportant citizen of Altdorf, minding her own business.");
    load_a_chat(20, ({ "*yell HELP, HELP!", "*yell HEEEEEELP!!" }));
    add_money(random(500));
}

static void
setup_beggar() 
{
    set_long("A poor beggar. " + capitalize(query_possessive()) + 
	     " hair is all a mess, and " + query_pronoun() + 
	     " is wearing dirty old rags.");
    load_chat(5, ({ "The beggar says: Please help me.\n",
		    "The beggar asks: Do you have any money?\n",
		    "The poor beggar pleads.\n",
		    "The beggar says: I have no life.\n"}));
    load_a_chat(20, ({ "The beggar says: nooo!\n",
		       "The beggar falls down to the ground.\n",
		       "The beggar pleads: Please spare my life.\n",
		       "The beggar growels in the dust.\n"}));
    setmin("limps in");
    setmout("limps");
    set_str(query_str() / 4);
    set_dex(query_dex() / 4);
    add_money(random(20));
}

static void
setup_sick() 
{
    set_long("A citizen, apparently very ill. Should not be too difficult " +
	     "to mess up good.");
    load_chat(5, ({ "The sick citizen coughs.\n",
		    "The sick citizen looks very ill.\n",
		    "A sick citizen complains: I hate the flue!\n" }));
    load_a_chat(20, ({ "The sick citizen shouts: help, help!\n",
		       "The sick citizen caughs up blood.\n",
		       "Sick citizen tried to flee but falls.\n" }));
    setmin("staggers in");
    setmout("staggers");
    set_str(query_str() / 3);
    set_dex(query_dex() / 3);
    add_money(random(250));
}

static void
setup_wounded() 
{
    set_long("A citizen with a big open wound, should not be too difficult to " +
	     "mess up good.");
    load_chat(5, ({ "The wounded citizen says: OUCH!\n" }));
    load_a_chat(20, ({ "The wounded citizen says: You have no pride, do you?\n",
		       "The wounded citizen complains: Hey, can't you see I'm " +
		       "already hurt?\n",
		       "Wounded citizen scoffs in disgust.\n" }));
    setmin("limps in");
    setmout("limps");
    set_str(query_str() / 2);
    set_con(query_con() / 2);
    add_money(random(250));
}

static void
setup_weak() 
{
    set_long("A very weak citizen, should not be too difficult to mess up good.");
    set_str(query_str() / 4);
    add_money(random(500));
}

static void
setup_strong() 
{
    set_long("You better watch out for this one, " + query_pronoun() +
	     " seems to be pretty strong.");
    load_chat(5, ({ "The strong citizen flexes " + query_possessive() + 
		    " muscles.\n" }));
    set_str(query_str() * 2);
    set_dex(query_dex() * 2);
    set_con(query_con() * 2);
    add_money(random(500));
}

static void
setup_busy() 
{
    set_long(capitalize(query_pronoun()) + " is quite busy, hurrying from " +
	     "place to place.");
    load_chat(5, ({ "The busy citizen hurries.\n",
		    "The busy citizen mumbles: Almost no time left.\n",
		    "Busy citizen seems very worried.\n" }));
    setmin("hurries in");
    setmout("hurries");
    add_money(random(500));
}

static void
setup_outstanding() 
{
    set_long("You look in awe at this respected citizen, not too afraid to " +
	     "show off " + query_possessive() + " wealth and good fortune.");
    load_a_chat(20, ({ "The outstanding citizen shouts: Seize #o!!!\n",
		       "The outstanding citizen whimpers: Please stop, " +
		       "maybe we can arrange a deal?\n",
		       "An outstanding citizen says: You will regret " +
		       "this!\n" }));
    add_money(100 + random(500) + random(500) + random(500));
}

static void
setup_poor() 
{
    set_long(capitalize(query_pronoun()) + " looks like " + query_pronoun() +
	     " could use some cash.");
    load_chat(5, ({ "The poor citizen mumbles: I wish I had some money..\n" }));
    add_money(random(20));
}

static void
setup_proud() 
{
    set_long(capitalize(query_pronoun()) + " must be very proud, walking " +
	     "with " + query_possessive() + "nose high up in the air.");
    add_money(random(500));
}

static void
setup_greedy() 
{
    set_long("You spot a spark in " + query_possessive() + 
	     " eyes leaving no doubt.");
    add_money(random(750));
}

static void
setup_ugly() 
{
    set_long("Urk, looking that bad in public should be forbidden...");
    load_chat(5, ({ "You feel the urge to throw up seeing that ugly citizen.\n" }));
    add_money(random(500));
}

static void
setup_handsome() 
{
    load_chat(5, ({ "You feel the urge to whistle after " + 
		    query_name() + ".\n" }));
    set_long(capitalize(query_pronoun()) + " is so handsome you could watch " + 
	     query_objective() + " forever.");
    add_money(random(500));
}
