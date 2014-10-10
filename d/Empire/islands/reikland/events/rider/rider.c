#include "/d/Empire/islands/reikland.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_male();
    set_name("old man");
    set_short("a sinew old man");
    set_long("A sinew old man with a mad expression in his red, " +
             "gleaming eyes.");
    add_id(({ "man", "sinew man", "old man" }));
    set_level(29);
    set_hp(666);
    set_wc(20);
    set_ac(15);
    set_al(-750);
    set_aggressive(1);
    set_scary(1);
    set_bored_secs(300);
    add_property("unarmed_damage_type", "claw");
    add_money(500 + random(1000));
    add_hook("__fight_beat", store_fp("maybe_drink"));
    load_a_chat(10, ({
        "*emote screams: THE SOULBLADE NEEDS YOUR SOUL!!",
        "*emote screams: DIE, HUMAN ONE!",
        "*emote screams: SAY YOUR PRAYERS!",
        "*emote screams: LET ME HAVE YOUR SOUL!!"
    }));
    add_eq(parse_path("potion"), 3);
    EMP_D_ARMOUR->add_unique(parse_path("helmet"), 125);
    EMP_D_WEAPON->add_unique(parse_path("sword"), 150);
}

static void 
maybe_drink(object foe) 
{
    int prev;
    if ((prev = query_hp()) > 256 || !objectp(present("potion"))) {
        return;
    }
    command("drink potion");
    command("drop empty bottle");
    command((prev < query_hp()) ? "say Ahhhh!" : "bleh");
}
