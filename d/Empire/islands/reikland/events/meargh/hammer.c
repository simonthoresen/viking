#include "/d/Empire/islands/reikland.h"

inherit EMP_I_WEAPON;

static void
create() 
{
    ::create();
    set_name("Bonecrusher");
    set_short("an enormous eog hammer");
    set_long("An enormously big and heavy hammer whose head is made of " +
             "silver laen, tinted pitch black.");
    set_info("This is the infamous " + bold("Bonecrusher") + ". Anything " +
             "remotely alive should shiver and fear this incredible weapon " +
             "of destruction.");
    add_id(({ "hammer", "eog hammer", "enormous hammer" }));
    set_class(15);
    set_value(2222);
    set_weight(8);
    set_hit_func(this_object());
    set_damage_type(({ "blunt", "blunt", "impact" }));
    add_property(({ "eog", "artifact" }));
    add_property("wield_msg", "Jesus, this hammer is heavy!\n");
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));  
}

static void 
on_wield(object obj, string hands) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->add_hook("__fight_beat", store_fp("maybe_crush"));
}

static void
on_remove() 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->remove_hook("__fight_beat");
}

public void
maybe_crush(object foe) 
{
    object ply, env, *arr;
    int i, len;
    if (!objectp(ply = query_wield()) ||
        !objectp(env = environment(ply)) ||
        env->query_property("no_special_attack"))
    {
        return;
    }
    for (i = 0, len = sizeof(arr = ply->query_attackers()); i < len; ++i) {
        if (!objectp(foe = present(arr[i], env)) ||
            foe->query_dead() ||
            foe->query_hp() > 75) 
        {
            continue;
        }
        tell_object(ply, "You accidentily SMASH " + foe->query_name() + 
                    "'s face as you swing your hammer around!\n");
        EMP_D_COMBAT->hit_player(ply, foe, 666, "Impact", 0, this_object());
        EMP_D_COMBAT->spray_blood(env, 50);
    }
}

static mixed
weapon_hit(object foe) 
{
    object ply, env;
    int val;
    if (!objectp(ply = query_wield())) {
        return 0;
    }
    val = ply->query_con();
    if (random(100) < 100 - (100 * val) / (val + 10)) {
        ply->command("pant");
        return "miss";
    }
    return 85;
}
