#include "/d/Empire/islands/altdorf.h"

#define POISON_CHANCE       13
#define MAX_POISON_DAMAGE   50
#define MAX_RECHARGE        20

inherit I_WEAPON;

private int _charges;

static void
create()
{
    ::create();
    _charges = 50;
    set_name("Thief's dagger");
    set_short("a stained dagger");
    set_long("The dagger seems to be coated with an unhealthy-looking " +
	     "green substance.");
    add_id(({ "thiefs dagger", "dagger", "stained dagger", "coated dagger" }));
    add_item("stain", "It looks like a stain of poison mixed with blood.");
    add_item("poison", "It might be poison or it might be blood.");
    add_item("blood", "It might be blood or it might be poison.");
    set_weight(1);
    set_value(210);
    set_class(8);
    set_damage_type("pierce");
    set_break_chance(10);
    set_break_msg(bold("Thief's dagger breaks in half!\n"));
    add_property(({ "iron", "magic" }));

    add_hook("__reset", store_fp("on_reset"));
    add_hook("__weapon_hit", store_fp("on_weapon_hit"));
}

static void
on_reset(int flag)
{
    object env;
    if (!objectp(env = environment()) ||
	_charges >= MAX_RECHARGE)
    {
	return;
    }
    message("", "There is a funny smell from the dagger.\n", env);
}

static int
on_weapon_hit(object foe)
{
    object ply, env;
    if (!objectp(ply = query_wield()) ||
	!objectp(foe) ||
	!objectp(env = environment(foe)) ||
	_charges <= 0 ||
	random(100) >= POISON_CHANCE)
    {
	return 0;
    }
    --_charges;
    tell_room(env, "%^L_GREEN%^" + foe->query_name() + " screams in pain as " +
	      ply->query_name() + "'s dagger fills " + foe->query_objective() +
	      " with lethal poison!%^END%^\n",
	      ({ foe, ply }));
    tell_object(ply, "%^L_GREEN%^" + foe->query_name() + " screams in pain " +
		"as your dagger fills " + foe->query_objective() +
		" with lethal poison!%^END%^\n");
    tell_object(foe, "%^L_GREEN%^Pain stings you in the heart from " +
		ply->query_name() + "'s poison!!!%^END%^\n");

    foe->set_busy_next_round(foe->query_name() +
                             " recovers from the poison.\n");
    return MAX_POISON_DAMAGE / 2 + random(MAX_POISON_DAMAGE / 2);
}
