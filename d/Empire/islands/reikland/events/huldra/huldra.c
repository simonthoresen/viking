#include "/d/Empire/islands/reikland.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_name("Huldra");
    set_short("a beautiful woman with soft blonde hair");
    set_long("Her bare skin is dazzlingly pale and her forms girlishly " +
             "perfect. She has enormous hair covering the nude body to the " +
             "knees. You realize that this is the fabled Huldra. She is so " +
             "beautiful you would like to spend the rest of your life with " +
             "her. Maybe you will?");
    add_id(({ "beautiful woman", "woman" }));
    set_female();
    set_race("shebitch");
    set_level(24);
    set_str(60);
    set_dex(60);
    set_hp(2500);
    set_al(-1500);
    set_wc(30);
    set_ac(15);
    set_light(1);
    set_scary(1);
    set_bored_secs(300);
    add_property("unarmed_damage_type",({ "claw", "bite" }));
    add_property("unarmed_weapon_name", "nails");
    add_property("no_headchop");
    add_skill("resist_blunt", 30);
    add_skill("resist_cold", 60);
    add_skill("seduction", 5);
    EMP_D_ARMOUR->add_unique(parse_path("ring"), 150, "ring");
    load_chat(20, ({
        "*dance bgirl",
        "*smile sug",
        "*fondle fon",
        "*say You're soo cute.",
        "*emote is hornily.",
        "*emote polishes one of her nails.",
        "*emote sings merrily: I'm too sexy for my body, too sexy for my body!",
        "*say I'm in a good mood tonight.",
        "*emote stares at you through the corner of her eye.",
        "*say There aren't very many men visiting me nowadays..."
    }));
    set_combat_arr(({
        1, "", "kissed", 0, 
	5, " with her sharp nails", "grazed", 0,
	10, " seductively", "bites", 0,
	25, " shredding off skin with her hair", "whipped", 0, 
	50, " making terrible scars", "clawed",0,
	100, " in the neck leaving a vein gaping open", "bites", 0
    }));
    load_a_chat(40, ({
	"*yell I WANT you!!!",
	"*swear",
	"Huldra screams out in pain.\n",
	"Huldra kills you softly with her claws.\n",
	"Huldra casts a spell that sputters and dies.\n",
	"Huldra gazes innocently at you.\n",
	"Huldra fondles you fondly.\n"
    }));
    add_hook("__receive_feeling", store_fp("on_receive_feeling"));
    add_hook("__bnotify_attack", store_fp("on_bnotify_attack"));
    add_hook("__battack", store_fp("on_battack"));
    add_hook("__choose_target", store_fp("on_choose_target"));
    add_hook("__kill", store_fp("on_kill"));
    add_hook("__bdie", store_fp("on_bdie"));
}

static void
on_receive_feeling(string verb, string adv, object ply) 
{
    if (!objectp(ply) || ply->query_male()) {
	return;
    }
    command("scream slut");
    do_attack(ply);
}

static void
on_bnotify_attack(object ply) {
    if (!objectp(ply)) {
	return;
    }
    if (ply->query_male()) {
	command("beg swe " + ply->query_real_name());
	make(parse_path("curse"), ply);
	return;
    } 
    command("emote shrieks: BEGONE BEFORE I TEAR YOU APPART LIMB BY LIMB!");
    command("scare " + ply->query_real_name());
    ply->run_away();
}

static object
on_choose_target(object *arr) 
{
    if (!arrayp(arr) || sizeof(arr) == 0) {
	return 0;
    }
    return sort_array(arr, "cmp_target")[0];
}

static void
on_kill(object victim, object killer) 
{
    string str;
    if (!objectp(victim)) {
	return;
    }
    if (victim->query_male()) {
	command("sob");
    } else {
	command("cackle");
	command("get all from corpse");
	command("get all");
	command("flex");
    }
    command("yell " + capitalize(victim->query_real_name()) + " has just " +
	    "learned not to mess with me!");
}

public int
on_bdie(object ply) 
{
    int val;
    if (!objectp(ply) || ply->query_male()) {
	command("tell " + ply->query_real_name() + " How could you?");
	command("cry");
	return 0;
    }
    if ((val = ply->query_sp()) <= 0) {
	return 0;
    }
    command("beam bgirl " + ply->query_real_name());
    reduce_hit_point(-val * 3);
    ply->reduce_spell_point(val);
    return 1;
}
