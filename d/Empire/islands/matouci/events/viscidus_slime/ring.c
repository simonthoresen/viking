#include "/d/Empire/empire.h"

inherit EMP_I_ARMOUR;

static void
create() 
{
    ::create();
    set_name("Fury of Viscidus");
    set_short("ring of the giant slime");
    set_long("It looks like a donut made of green jell-o.");
    add_property(({ "magic" }));
    add_property("vuln_fire", 100);
    set_type("ring");
    set_ac(0);
    set_weight(1);
    set_wear_modifier("str", 1, 0);
    set_wear_modifier("dex", 1, 0);
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
}

static void
on_wear() 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->add_hook("__damage_dealt", store_fp("on_wearer_damage_dealt"));
}

static void
on_remove() 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__damage_dealt");
}

public void 
on_wearer_damage_dealt(int dmg, string type, object foe,
                       string loc, object wpn)
{
    EMP_D_CRITICAL->damage_dealt(query_worn_by(), foe, dmg, loc);
}
