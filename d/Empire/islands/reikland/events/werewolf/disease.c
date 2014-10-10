#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ITEM;

private int _wolf;

static void
create() 
{
    ::create();
    _wolf = 0;

    set_name("disease");
    set_short(0);
    set_long("You are becoming a wolf!");
    add_id(source_file_name());
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public string 
extra_look() 
{
    return capitalize(environment()->query_pronoun()) + " looks ill";
}

private void
become_wolf() 
{
    object ply, env;
    if (!objectp(ply = environment()) ||
        !living(ply))
    {
        return;
    }
    if (objectp(env = environment(ply))) {
        tell_object(ply, "You howl in pain as you turn into a werewolf!\n");
        tell_room(env, ply->query_name() + " howls in pain as he turns into " +
                  "a werewolf.\n", ({ ply }));
    }
    ply->query_worn_armour()->wear_out(100);
    ply->command("unwield all");
    ply->set_modifier("werewolf:str", "str", "special", 11);
    ply->set_modifier("werewolf:dex", "dex", "special", 11);
    ply->set_modifier("werewolf:con", "con", "special", 11);
    ply->set_modifier("werewolf:int", "int", "special", -5);
    ply->set_modifier("werewolf:ac",  "ac",  "special", 5);
    ply->add_hook("__bwield", store_fp("prevent_wield"));
    ply->add_hook("__bwear", store_fp("prevent_wear"));
    ply->add_hook("__beat", store_fp("prevent_eat"));
    ply->add_hook("__bdrink", store_fp("prevent_drink"));
    ply->add_hook("__battack", store_fp("prevent_attack"));
    ply->add_hook("__bshort", store_fp("prevent_short"));
    _wolf = 1;
}

private void
become_human() 
{
    object ply, env;
    if (!objectp(ply = environment()) ||
        !living(ply))
    {
        return;
    }
    if (objectp(env = environment(ply))) {
        tell_object(ply, "You calm down and become human once again.\n");
        tell_room(env, "The werewolf calms down and becomes human.\n", 
                  ({ ply }));
    }
    ply->remove_modifier("werewolf:str");
    ply->remove_modifier("werewolf:dex");
    ply->remove_modifier("werewolf:con");
    ply->remove_modifier("werewolf:int");
    ply->remove_modifier("werewolf:ac");
    ply->remove_hook("__bwield");
    ply->remove_hook("__bwear");
    ply->remove_hook("__beat");
    ply->remove_hook("__bdrink");
    ply->remove_hook("__bshort");
    _wolf = 0;
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && living(from)) {
        if (_wolf) {
            become_human();
        }
        tell_object(from, "You feel better.\n");
        from->remove_hook("__heart_beat");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "You feel ill.\n");
        to->add_hook("__heart_beat", store_fp("on_diseased_heart_beat"));
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public int
prevent_wield(object obj, string hands) 
{
    tell_object(previous_object(), "Your claws will do.\n");
    return 1;
}

public int
prevent_wear(int silent, object obj) 
{
    tell_object(previous_object(), "Your armour doesn't fit.\n");
    return 1;
}

public int
prevent_eat(object obj) 
{
    tell_object(previous_object(), "You don't feel like it.\n");
    return 1;
}

public int
prevent_drink(object obj) 
{
    tell_object(previous_object(), "You don't feel like it.\n");
    return 1;
}

public int
prevent_attack(object foe) 
{
    return 1;
}

public string
prevent_short() 
{ 
    return "a werewolf"; 
}

public void
on_diseased_heart_beat() 
{
    object ply, foe;
    if (!objectp(ply = environment()) || !living(ply)) {
        return;
    }
    ply->reduce_hit_point(-5);
    if (objectp(foe = ply->query_attack())) {
        int i, len;
        if (!_wolf) {
            become_wolf();
        }
        for (i = 0, len = min(3, ply->query_level() / 9); i < len; ++i) {
            EMP_D_COMBAT->hit_player(ply, foe, random(ply->query_str() / 2) + 
                                     random(ply->query_dex() / 2), "claw");
        }
    } else if (_wolf) {
        become_human();
    }
}
