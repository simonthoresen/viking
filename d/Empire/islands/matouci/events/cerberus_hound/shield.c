#include "/d/Empire/empire.h"

inherit I_ARMOUR;

static void
create() 
{
    ::create();
    set_name("Bulwark of Cerberus");
    set_short("the bulwark of Cerberus");
    set_long("This is what remains of Cerberus' skullbone. It is " +
             "covered in razor sharp spikes that are glowing with fire " +
             "and electricity. You can wear it like a shield.");
    set_type("shield");
    add_id(({ "carapace", "bulwark", "skullbone" }));
    set_ac(1);
    set_weight(5);
    add_property(({ "leather", "bone", "artifact" }));
    set_wear_modifier("ac", 3, 666);
    set_wear_modifier("con", 2, 11); 
    set_wear_modifier("resist_fire", 25, 666);
    set_wear_modifier("resist_electricity", 25, 666);
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
    ply->add_hook("__fight_beat", store_fp("on_fight_beat"));
    ply->add_hook("__hit_player", store_fp("on_hit_player"));
}

static void
on_remove(int silent) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__fight_beat");
    ply->remove_hook("__hit_player");
}

private void
burn_player(object ply, object foe, object env) 
{
    tell_room(env, "%^B_RED%^%^L_YELLOW%^" + query_name() + 
              " breathes fire!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 16 + random(32), 
                             "Fire", 0, this_object());
}

private void
shock_player(object ply, object foe, object env) 
{
    tell_room(env, "%^B_BLUE%^%^BOLD%^%^WHITE%^" + query_name() + 
              " spews lightning!%^END%^\n");
    if (EMP_D_COMBAT->hit_player(ply, foe, 16 + random(16), 
                                 "electricity", 0, this_object()) > 8) 
    {
        EMP_D_COMBAT->stun_player(foe, random(3));
    }
}

public void
on_fight_beat() 
{
    object ply, foe, env;
    if (!objectp(ply = previous_object()) ||
        !objectp(foe = ply->query_attack()) ||
        !objectp(env = environment(ply)))
    {
        return;
    }
    if (random(100) > 15) {
        return;
    }
    if (random(100) > 25) {
        burn_player(ply, foe, env);
    } else {
        shock_player(ply, foe, env);
    }
}

public int 
on_hit_player(int dmg, string dtype, object foe, string loc, int prot_mod,
              int resist_mod, int vuln_mod, int ac_mod, object weapon) 
{
    object ply, env;
    string gen;
    if (!objectp(ply = previous_object()) || 
        !objectp(env = environment(ply)) ||
	!objectp(present(foe, env)) ||
        random(100) > 25 ||
        ac_mod >= 0) 
    {
        return 0;
    }
    gen = I_GRAMMAR->genitive(ply->query_name());
    message("hityou", "You cut yourself on " + gen + " shield.\n", foe);
    message("youhit", foe->query_name() + " cuts " + foe->query_objective() + 
            "self on your shield.\n", ply);
    tell_room(env, foe->query_name() + " cuts " + foe->query_objective() + 
              "self on " + gen + "'s shield.\n", ({ ply, foe }));
    EMP_D_COMBAT->wound_player(ply, foe, random(-ac_mod));
    return 0;
}
