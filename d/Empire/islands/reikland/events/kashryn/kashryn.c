#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_name("Kashryn");
    set_short("a black hooded figure");
    set_long("You see a small human with white hair and pale skin. "+
	     "The smell of old spices and decay tell you that this person " +
             "must be some kind of magic user. He is smiling at you.");
    add_id(({ "hooded figure", "figure" }));
    set_level(30);
    set_male();
    set_hp(1650);
    set_race("human");
    set_str(45);
    set_dex(45);
    set_ac(15);
    set_int(60);
    set_sp(2000);
    set_wc(35);
    set_ac(4);
    set_aggressive(0);
    set_al(-3060);
    set_bored_secs(300);
    setmin("walks in");
    setmout("walks");
    add_property(({ "undead", "necromancer" }));
    add_property("unarmed_damage_type", ({ "blunt", "bite" }));
    add_cmdpath("/d/Necro/com/");
    add_hook("__kill", store_fp("animate_corpse"));
    add_skill("necromancy", 200);
    add_skill("two_weapon", 100);
    add_money(1000 + random(4000));
    load_chat(10, ({ "*animate corpse" }));
    load_a_chat(30, ({ 
        "*chill", "*chill", "*chill", 
        "*bloodboil", "*bloodboil", "*bloodboil",
        "*disease", 
        "*shield",
        "*summon", 
        "*snarl dem", 
        "*scream",
        "*yell: I will pull your Soul from the land of the Dead to serve me!"
    }));
    EMP_D_WEAPON->add_weapon(75);
}

static void 
animate_corpse(object victim, object killer) 
{
    call_out("command", 2, "animate corpse");
}

public varargs int
do_attack(object foe, object obj) 
{
    if (objectp(foe) && foe->query_property("master") == query_real_name()) {
        return 0;
    }
    return ::do_attack(foe, obj);
}
