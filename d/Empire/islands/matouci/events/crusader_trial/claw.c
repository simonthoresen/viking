#include "/d/Empire/empire.h"

#define CHANCE_PROC    10
#define CHANCE_TOXIN   20

inherit EMP_I_WEAPON;

private int _proc_bias;

static void
create() 
{
    ::create();
    _proc_bias = 0;

    set_name("Claw of the Crusader");
    set_short("a set of metal blades");
    set_long("Your heavy leather gloves are doubling as fist weapons.");
    add_id(({ "claw", "blades", "metal blades" }));
    set_weight(1);
    set_value(3333);
    set_damage_type("claw");
    set_class(0);
    add_property("unremovable");
    add_property("protected", 100);
    add_property(({ "tagged", "steel" }));
    set_wield_modifier("dex", 1, 1);
    add_hook("__weapon_hit", store_fp("on_weapon_hit"));
}

private void
do_toxin(object ply, object foe, int val) 
{
    object obj;
    if (!objectp(ply) || !objectp(foe)) {
        return;
    }
    tell_object(ply, "%^B_GREEN%^%^L_YELLOW%^Paralyzing toxins shoot from " +
                "your gloves!%^END%^\n");
    tell_room(environment(foe), "%^B_GREEN%^%^L_YELLOW%^Paralyzing toxins " +
              "shoot from " + ply->query_name() + "'s gloves.%^END%^\n", 
              ({ ply })); 
    obj = new(resolve_path("toxin"));
    obj->set_amount(val);
    obj->set_hitter(ply);
    EMP_D_COMBAT->apply_liquid(foe, obj);
}

private void
do_fire(object ply, object foe, int val) 
{
    object obj;
    if (!objectp(ply) || !objectp(foe)) {
        return;
    }
    tell_object(ply, "%^B_RED%^%^L_YELLOW%^Liquid fire shoots from your " +
                "gloves!%^END%^\n");
    tell_room(environment(foe), "%^B_RED%^%^L_YELLOW%^Liquid fire shoots " +
              "from " + ply->query_name() + "'s gloves.%^END%^\n", ({ ply })); 
    obj = new(resolve_path("fire"));
    obj->set_amount(val);
    obj->set_hitter(ply);
    EMP_D_COMBAT->apply_liquid(foe, obj);
}

static int
on_weapon_hit(object foe) 
{
    object ply, env;
    if (objectp(ply = query_wield()) &&
	objectp(env = environment(ply)) &&
        !env->query_property("no_special_attack") &&
        random(100) < CHANCE_PROC + (++_proc_bias)) 
    {
        _proc_bias = 0;
        if (random(100) < CHANCE_TOXIN) {
            do_toxin(ply, foe, 1 + random(2));
        } else {
            do_fire(ply, foe, 20 + random(20));
        }
    }
    return 35;
}
