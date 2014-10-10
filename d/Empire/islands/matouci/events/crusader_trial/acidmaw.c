#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "crusader_trial/serpent";

static void
create() 
{
    ::create();
    set_name("Acidmaw");
    set_short("the TOXIC Acidmaw serpent");
    set_long("This snake is almost 17 feet long, and it is 1 foot wide at " +
             "the neck. When stood upright, it look down on you. It has a " +
             "flattened neck, giving it a distinctive hood. Even though its " +
             "scaly skin glistens, it is actually dry to the touch. There " +
             "is a greenish aura about its head.");
    set_liquid("toxin");
    set_level(29);
    set_hp(10000);
    set_wc(10);
    set_ac(20);
    set_aggressive(1);
    add_property("unarmed_damage_type", ({ "acid", "bite" }));
    add_skill("prot_acid", 100);
    add_skill("vuln_fire", 100);
    load_a_chat(50, ({
        store_fp("do_bite"),
        store_fp("do_bite"),
        store_fp("do_spit"),
    }));
}

private object
random_attacker() 
{
    object *arr;
    int len;
    if (!arrayp(arr = query_attackers()) || 
        (len = sizeof(arr)) == 0) 
    {
        return 0;
    }
    return arr[random(len)];
}

static void
do_spit(object ply, object foe) 
{
    command("cough");
    call_out("on_spit", 1);
}

public void
on_spit() 
{
    object env, foe;
    if (!has_gland() ||
        !objectp(env = environment()) ||
        !objectp(foe = random_attacker()) ||
        !objectp(present(foe, environment())))
    {
        return;
    }
    tell_object(foe, "Acidmaw spits on you!\n");
    tell_room(env, "Acidmaw spits on " + foe->query_name() + ".\n",
              ({ foe }));
    EMP_D_COMBAT->hit_player(this_object(), foe, 
                             scale_damage(25 + random(25)), "acid");
    EMP_D_COMBAT->apply_liquid(foe, create_liquid(5 + random(5)));
}

static void
do_bite(object ply, object foe) 
{
    command("emote bares its teeth.");
    call_out("on_bite", 1);
}

public void
on_bite() 
{
    object foe, env, obj;
    if (!objectp(env = environment()) ||
        !objectp(foe = query_attack()) ||
        !objectp(present(foe, env))) 
    {
        return;
    }
    if (EMP_D_COMBAT->hit_player(this_object(), foe, 
                                 scale_damage(25 + random(50)), "bite") < 50) 
    {
        return;
    }
    EMP_D_COMBAT->wound_player(this_object(), foe, 
                               scale_damage(25 + random(25)));
    EMP_D_COMBAT->spray_blood(env, 10);
    if (objectp(obj = create_liquid(2 + random(5)))) {
        obj->move(foe);
    }
}
