#include "/d/Empire/empire.h"

inherit EMP_I_ARMOUR;

static void
create() 
{
    ::create();

    set_name("Fenrir's hide");
    set_short("the fur hide of Fenrir");
    set_long("These are the bloody remains of Fenrir's hide. They " +
             "are remarkably warm and comfortable to wear.");
    add_id(({ "fure", "hide", "fure hide", "cloak" }));
    set_type("cloak");
    set_ac(1);
    set_weight(2);
    add_property("fur");
    set_wear_modifier("prot_cold", 25, 666);
    set_wear_modifier("resist_cold", 100, 666);
    set_wear_modifier("vuln_fire", 25, 666);
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
    ply->add_hook("__fight_beat", store_fp("on_wearer_fight_beat"));
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

public void
on_wearer_fight_beat(object foe) 
{
    object ply, env, pet;
    if (!objectp(ply = previous_object()) ||
        !objectp(env = environment(ply))) 
    {
        return;
    }
    if (!ply->query_weapon(1)->is_fenrir_claw() ||
        !ply->query_weapon(2)->is_fenrir_claw() ||
        random(100) > 5) 
    {
        return;
    }
    tell_object(ply, "%^BOLD%^You unleash the spirit of Fenrir!%^END%^\n");
    pet = make(resolve_path("spirit"), env);
    pet->do_attack(foe);
}
