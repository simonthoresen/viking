#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_race("human");
    set_name("Barbarian");
    set_short("a big muscular human");
    set_long("A large hunk of flesh with raven black hair and protruding "+
             "muscles with thick bloodveins.");
    add_id(({ "big human", "muscular human", "man" }));
    set_male();
    set_level(20+random(10));
    set_str(55);
    set_dex(5);
    set_ac(20);
    set_hp(750);
    set_al(-100);
    set_aggressivity(10);
    set_scary(1);
    set_bored_secs(300);
    setmin("stomps in");
    setmout("stomps");
    add_skill("two_weapon", 100);
    add_money(1000 + random(3000));

    load_a_chat(90, ({
        "*emote screams: I'LL DANCE ON YOUR HEADS BASTARDS!!",
        "*emote screams: SUCK MY WEAPON, ASSHOLES!!!",
        "*emote screams: I'LL SMASH YOU LIKE AN INSECT!!!!",
        "*emote screams: UHHNNG!!!!",
        "*emote screams: ARRGGGGGGHHHHHH!!!!",
        "*emote screams: DIE DIE DIE DIE DIE!!!"
    }));

    add_eq(parse_path("amulet"));
    add_eq(parse_path("sword"));
    add_eq(parse_path("sword"));
    EMP_D_ARMOUR->add_armour(25);
    EMP_D_ARMOUR->add_armour(25);
}
