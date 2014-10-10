#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_MONSTER;

static void
create()
{
    object this;
    ::create();
    set_name("Berag");
    set_short("Executioner Berag of the Altdorf Guard");
    set_long("Berag is the sacked executioner of Altdorf.");
    add_id(({ "executioner", "man" }));
    set_male();
    set_race("human");
    set_level(23 + random(4));
    set_int(10 + random(6));
    set_str(40 + random(5));
    set_dex(25 + random(6));
    set_hp(1000 + random(500));
    add_money(900 + random(2000));
    set_al(-random(600) + random(700));
    set_wc(25);
    set_ac(6);
    set_scary(1);
    set_bored_secs(300);
    add_exp(500000);
    load_chat(5, ({
        "*emote looks to be in a VERY bad mood.",
        "*say Stupid dorks.",
        "*say Whomever gets in my way today, can say " +
            "hello to the devil for me.",
        "*yell It's so goddamn unfair!",
        "*say HOW can they DECIDE such a thing??",
        "*bleh",
        "*say Now I got nothing to do!",
        "*say What's the point of it all now?",
        "*say Everyone can go to hell!",
        "*sigh",
        "*swear"
    }));
    load_a_chat(40, ({
        "*yell You just did your LAST MISTAKE #N!",
        "*shout You don't have to come and help me, I can manage.",
        "*swear",
        "*groan",
        "*smile evi",
        "*say Beginning to sweat yet #N?",
        "*say Kiss my blade #N!!!",
        "*say That one was p-a-t-h-e-t-i-c!"
    }));
    if (!clonep(this = this_object())) {
        return;
    }
    add_eq(resolve_path("axe"));
    EMP_D_ARMOUR->add_armour(50 + random(50));
    EMP_D_ARMOUR->add_armour(50 + random(50));
}
