#include "/d/Empire/empire.h"

inherit EMP_I_ARMOUR;

private object _lclaw;
private object _rclaw;

static void 
create() 
{
    ::create();
    _lclaw = 0;
    _rclaw = 0;

    set_type("glove");
    set_name("Gloves of the Crusader");
    set_short("a pair of plated leather gloves");
    set_long("A pair of heavy leather gloves inset with steel plates.");
    add_id(({ "gloves", "leather gloves", "leather gloves" }));
    set_ac(1);
    set_weight(3);
    set_value(3333);
    add_property("protected", 100);
    add_property(({ "tagged", "steel", "leather" }));
    set_wear_modifier("str", 2, 2);
    add_hook("__wear", store_fp("on_wear")); 
    add_hook("__remove", store_fp("on_remove"));
}

static void
on_wear(int flag, object obj) 
{
    object ply, env;
    if (!objectp(ply = query_worn_by()) ||
	!objectp(env = environment(ply)) ||
	objectp(ply->query_weapon(1)) ||
	objectp(ply->query_weapon(2)) ||
	objectp(ply->query_worn_armour("shield")))
    {
        return;
    }
    tell_object(ply, "Sharp metal blades extend from your gloves.\n");
    if (objectp(_lclaw = make(resolve_path("claw"), ply))) {
        _lclaw->wield(0);
    }
    if (objectp(_rclaw = make(resolve_path("claw"), ply))) {
        _rclaw->wield(1);
    }
}

static void
on_remove(int flag) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    if (objectp(_lclaw) || objectp(_rclaw)) {
        tell_object(ply, "The metal blades retract into your gloves.\n");
    }
    if (objectp(_lclaw)) {
        _lclaw->destroy();
    }
    if (objectp(_rclaw)) {
        _rclaw->destroy();
    }
}

