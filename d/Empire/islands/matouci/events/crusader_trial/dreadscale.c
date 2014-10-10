#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "crusader_trial/serpent";

static void 
create() 
{
    ::create();
    set_name("Dreadscale");
    set_short("the FLAMING Dreadscale serpent");
    set_long("This snake is almost 17 feet long, and it is 1 foot wide at " +
             "the neck. When stood upright, it look down on you. It has a " +
             "flattened neck, giving it a distinctive hood. Even though its " +
             "scaly skin glistens, it is actually dry to the touch. There " +
             "are flames shooting about its head.");
    set_liquid("fire");
    set_level(29);
    set_hp(10000);
    set_wc(25);
    set_ac(20);
    set_aggressive(1);
    add_property(({ "warm", "hot", "fire" }));
    add_property("unarmed_damage_type", ({ "fire", "bite" }));
    add_skill("prot_fire", 100);
    add_skill("vuln_acid", 100);
    load_a_chat(75, ({
        store_fp("do_bite"),
        store_fp("do_bite"),
        store_fp("do_spray"),
    }));
}

static void
do_spray(object ply, object foe)
{  
    command("cough men");
    call_out("on_spray", 1);
}

public void
on_spray() 
{
    object env, obj;
    if (!has_gland() ||
        !objectp(env = environment()))
    {
        return;
    }
    tell_room(env, "Dreadscale sprays fire everywhere!\n");
    EMP_D_COMBAT->spray_liquid(env, create_liquid(25 + random(25)), 
                               ({ this_object(), query_partner() }));
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
    if (objectp(obj = create_liquid(50 + random(50)))) {
        obj->move(foe);
    }
}
