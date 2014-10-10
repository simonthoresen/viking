#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN;

static void
create()
{
    object this,ob;
    ::create();
    set_name("Brendan");
    set_short("a bearded old wizard named Brendan.");
    set_long("This guy reminds you of a mysterious raven. He has droopy " +
             "brown eyes that are like two bronze coins. His fine, curly, " +
             "beige hair is neck-length and is worn in an artistic style. " +
             "He is short and has a broad-shouldered build. His skin is " +
             "ruddy. He has a pointed chin. His wardrobe is unusual, and is " +
             "completely white.");
    add_id(({ "brendan", "wizard", "man", "old man", "bearded man" }));
    set_male();
    set_race("human");
    set_level(25);
    set_int(69);
    set_hp(1250);
    set_sp(2500);
    add_money(900 + random(500));
    set_al(0);
    set_wc(25);
    set_ac(19);
    set_bored_secs(300);
    add_exp(600000);
    if (!clonep(this = this_object())) {
        return;
    }
    load_chat(10, ({
        "*say Before God we are all equally wise - and equally foolish.",
        "*say It is always wise to look ahead, but difficult to look " +
            "further than you can see.",
        "*say The well bred contradict other people. The wise contradict " +
            "themselves. ",
        "*say Wise men don't need advice. Fools won't take it.",
        store_fp("do_chant"),
    }));
    load_a_chat(100, ({
        "*say Anger dwells only in the bosom of fools.",
        "*say Don't get the impression that you arouse my anger. You see, " +
            "one can only be angry with those he respects.",
        "*say Anger makes dull men witty, but it keeps them poor.",
        "*say Anger is a wind which blows out the lamp of the mind.",
        "*say Anger is an acid that can do more harm to the vessel in which " +
            "it is stored than to anything on which it is poured.",
        store_fp("do_drink"),
        store_fp("do_curse"),
        store_fp("attack"),
    }));
    EMP_D_ARMOUR->add_armour(80, "armour");
    EMP_D_ARMOUR->add_armour(80, "boot");
    EMP_D_ARMOUR->add_armour(80, "glove");
    add_eq(resolve_path("sword"), 1, resolve_path("ring"), 100);
}

static void
do_chant(object ply)
{
    object *arr, env;
    if (!objectp(env = environment()) ||
        !arrayp(arr = all_inventory(env)) ||
        !arrayp(arr = filter_array(arr, "isplayer", D_FILTER)))
    {
        return;
    }
    command("wave mag");
    call_out("cast_spell", 2, arr[random(sizeof(arr))], "aura");
}

static void
do_curse(object ply, object foe)
{
    if(!objectp(foe)) {
        return;
    }
    command("wave men");
    call_out("cast_spell", 2, foe, "curse");
}

static void
do_drink(object ply, object foe)
{
    command("emote takes a sip from a tiny blue flask.");
    reduce_spell_point(-666);
}

public void
cast_spell(object ply, string spell)
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    if (!objectp(present(ply, env)) ||
        objectp(ply->query_worn_armour("aura")))
    {
        command("sigh");
        return;
    }
    tell_object(ply, "Brendan casts a spell on you!\n");
    tell_room(env, "Brendan casts a spell on " + ply->query_name() + ".\n",
              ({ ply }));
    make(resolve_path(spell), ply);
}
