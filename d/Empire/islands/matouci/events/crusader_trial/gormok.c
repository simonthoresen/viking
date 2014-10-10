#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private int _anger;

static void
create() 
{
    ::create();
    _anger = 0;
    
    set_name("Gormok");
    set_short("Gormok the ULTRALISK");
    set_long("Gormok is a HUGE beast, at least ten times your size. It " +
             "resembles a carrion-beatle out of some horrible nightmare. " +
             "It has massive bone-like schytes for arms that look like they " +
             "could tear through anything.");
    add_property("unarmed_damage_type", ({ "bite", "claw", "Claw" }));
    set_level(28);
    set_aggressive(1);
    set_hp(5000);
    set_wc(40);
    set_dex(40);
    set_str(40);
    set_scary(1);
    set_bored_secs(300);
    add_exp(1500000);
		if (!random(7)) {
			EMP_D_ARMOUR->add_armour(100+random(100), "helmet");
		}
		EMP_D_ARMOUR->add_armour(100+random(100), "ring");
    load_a_chat(25, ({ store_fp("do_anger"), 
                       store_fp("do_baneling"),
                       store_fp("do_bite"),
                       store_fp("do_impale"),
                       store_fp("do_stomp"),
                       store_fp("do_swing") }));
}

private int
query_damage(int val) 
{
    return val + (val * _anger) / 100;
}

static void
do_anger(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, bold("\nGormok grows larger!\n\n"));
    _anger += 10 + random(10);
}

static void
do_baneling(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "\nGormok coughs up a BANELING!\n\n");
    make(resolve_path("baneling"), env);
}

static void
do_bite(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "Gormok takes a large bite out of " + foe->query_name() +
              ".\n", ({ foe }));
    tell_object(foe, "\nGormok takes a large bite out of you!\n\n");
    if (EMP_D_COMBAT->hit_player(ply, foe, query_damage(30 + random(70)), 
                                 "bite") < 50) 
    {
        return;
    }
    EMP_D_COMBAT->wound_player(ply, foe, query_damage(20 + random(30)));
    EMP_D_COMBAT->spray_blood(env, 10);
}

static void
do_impale(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "Gormok impales " + foe->query_name() + " on one of " +
              "its scythes.\n", ({ foe }));
    tell_object(foe, "\nGormok impales you on one of its scythes!\n\n");
    EMP_D_COMBAT->hit_player(ply, foe, 50 + random(50), "Pierce");
    EMP_D_COMBAT->wound_player(ply, foe, 300 + random(200));
}

static void
do_stomp(object ply, object foe) 
{
    object env;
    int dmg;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "Gormok throws itself at " + 
              foe->query_name() + ".\n", ({ foe }));
    tell_object(foe, "\nGormok throws itself at you!\n\n");
    dmg = EMP_D_COMBAT->hit_player(ply, foe, query_damage(50 + random(50)),
                                   "impact");
    if (dmg > 75) {
        EMP_D_COMBAT->throw_player(foe, dmg / 30);
    }
}

static void
do_swing(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "\nGormok swings its scythes across the room.\n\n");
    map_array(all_inventory(env), "apply_swing");
}

static void
apply_swing(object foe) 
{
    if (!objectp(foe) || !living(foe) || foe->query_invis() || 
        foe->is_crusader()) 
    {
        return;
    }
    EMP_D_COMBAT->hit_player(this_object(), foe, query_damage(20 + random(20)),
                             "slash");
}

public int
is_crusader() 
{ 
    return 1; 
}
