#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ARMOUR;

private int _bias;

static void
create() 
{
    ::create();
    _bias = 0;
    set_type("ring");
    set_name("Ring of Seduction");
    set_short("a BEAUTIFUL copper ring");
    set_long("Oh No! The ring isn't beautiful at all when you look closer " +
             "at it. The ring is so ugly, it is beyond description. And it " +
             "is covered with a heavy layer of dirt!");
    set_info("This ring will bring the uncontrollable seductive powers of " +
             "Huldra to you! It will do _MORE_ damage to the victim than it " +
             "will feed the wearer. It is covered in magical dirt.");
    add_id(({ "beautiful ring", "ugly ring", "copper ring" }));
    add_item(({ "dirt", "layer of dirt" }), "The dirt seems to be pretty " +
             "stuck to the ring. You have a feeling that it is probably " +
             "best to leave the dirt be. It looks magic!");
    set_weight(3);
    set_value(1500);
    set_ac(0);
    add_property(({ "artifact", "copper" }));
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
}

static void 
on_wear(int silent, object obj) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->add_hook("__fight_beat", store_fp("maybe_seduce"));
}

static void
on_remove(int silent) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__fight_beat");
}

private string
query_random_noise(object ply) 
{
    string name;
    name = capitalize(ply->query_real_name());
    switch (random(13)) {
    case 0: return "Maybe you should just let " + name + " win?";
    case 1: return "You feel weak in the presence of " + name + "!";
    case 2: return "You feel old in the magnificent presence of " + name + "!";
    case 3: return name + " looks GREAT!";
    case 4: return "Do not flee from " + name + "!";
    case 5: return "Go with " + name + "...";
    case 6: return "Do not resist " + name + ".";
    case 7: return "Surrender to " + name + ", or die without hope.";
    case 8: return "Give up now.";
    case 9: return "Follow " + name + ", and live forever!";
    case 10: return "Join " + name + "!";
    case 11: return "Why are you hurting " + name + "?";
    case 12: return "You are confused.";
    }
}

public void
maybe_seduce(object foe) 
{
    object ply, env;
    int val;
    if (!objectp(foe) ||
        !objectp(ply = query_worn_by()) ||
        !objectp(env = environment(ply)) ||
        ply->query_gender() == foe->query_gender() ||
        foe->query_property("undead") ||
        env->query_property("no_mattack") ||
        random(100) > ply->query_skill("seduction") + _bias)
    {
	_bias += 3;
        return;
    }
    _bias = 0;
    ply->command("seduce " + foe->query_real_name());
    ply->set_busy_next_round();
    if (random(2 * ply->query_int()) < random(foe->query_int())) {
        foe->command("scoff");
        return;
    }
    tell_object(foe, "\n\n" + bold(query_random_noise(ply)) + "\n\n\n");
    val = EMP_D_COMBAT->hit_player(ply, foe, 50 + random(100), "magic");
    ply->reduce_hit_point(-val / 2);
}
