#include "/d/Empire/islands/reikland.h"

inherit EMP_I_WEAPON;

private mapping _dmg_done;
private int     _last_kill;

static void
create() {
    ::create();
    _dmg_done  = ([ ]);
    _last_kill = 0;

    set_name("Dagger of Wrath");
    set_short("a black-bladed curved knife");
    set_long("It is a curved knife the size of a short-sword with a black, " +
             "curved blade. The hilt is wrapped with leather straps of " +
             "various colors.");
    add_id(({ "knife", "curved knife", "dagger" }));
    set_class(5);
    set_weight(1);
    set_value(444);
    set_damage_type("pierce");
    set_hit_func(this_object());
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
}

public int
weapon_hit(object foe) 
{
    return random(100) < 25 ? 10 : 0;
}

static void
on_wield(object obj, string hands) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->add_hook("__damage_done", store_fp("maybe_riposte"));
    ply->add_hook("__bkill", store_fp("fancy_kill"));
    ply->add_hook("__kill", store_fp("eat_giblet"));
}

static void
on_remove() 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->remove_hook("__damage_done");
    ply->remove_hook("__bkill");
    ply->remove_hook("__kill");
}

public int
fancy_kill(object victim, object killer) 
{
    int now;
    now = time();
    if (_last_kill == now) {
        return 0;
    }
    _last_kill = now;
    EMP_D_CRITICAL->hit_player(killer, victim, 100, 
                               EMP_D_LIMB->query_random_limb(victim, 1));
    return 0;
}

public void
eat_giblet(object corpse, object killer) 
{
    object env;
    string gib;
    if (!objectp(corpse) || !objectp(killer) || 
        !objectp(env = environment(corpse)) ||
        !objectp(present(killer, env)))
    {
        return;
    }
    gib = ({ 
        "a bloody kidney",
        "a part of the brain",
        "the still-beating heart" 
    })[random(3)];
    tell_object(killer, "You cut " + gib + " out of " + 
                corpse->query_cap_name() + " and eat it!\n");
    tell_room(env, killer->query_name() + " cuts " + gib + " out of " +
              corpse->query_cap_name() + " and eats it!\n", ({ killer }));
    killer->heal_self(corpse->query_level());
}

public void
maybe_riposte(int dmg, string type, object foe, string loc) 
{
    string foe_name;
    object ply, env;
    if (!objectp(foe) || 
        !objectp(ply = query_wield()) ||
        !objectp(env = environment(ply)) ||
        !objectp(present(foe, env)) ||
        !living(foe) ||
        foe == ply)
    {
        return;
    }
    if (interactive(foe) && !env->query_property("anarchy")) { 
        return;
    }
    foe_name = foe->query_real_name();
    _dmg_done[foe_name] = _dmg_done[foe_name] + dmg;
    if (_dmg_done[foe_name] < 70 ||
        ply->query_busy_next_round()) 
    {
        return;
    }
    dmg = min(_dmg_done[foe_name], 10 + 6 * ply->query_str());
    ply->command("say TAKE THIS!!");
    EMP_D_COMBAT->hit_player(ply, foe, dmg / 2 + random(dmg / 2), "pierce", 
                             0, this_object());
    _dmg_done = ([ ]);
}
