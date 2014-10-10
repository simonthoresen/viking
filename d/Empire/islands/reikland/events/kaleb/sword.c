#include "/d/Empire/empire.h"

inherit weapon EMP_I_WEAPON;
inherit align  EMP_I_ALIGNED;

private int _life;
private int _bias;

static void 
create() 
{
    weapon::create();
    align::create();
    _life = 0;
    _bias = 0;

    set_name("Longsword of Kaleb");
    set_short("a white alabaster longsword");
    set_long("A white alabaster longsword with superb sharp edges.");
    add_id(({ "sword", "longsword", "alabaster sword", "white longsword" }));
    set_info("This is Shianul - The Chaos Cleaver.");    
    set_class(20);
    set_weight(6);
    set_value(2222);
    set_damage_type("slash");
    set_min_align(ALIGN_GOOD);
    set_hit_func(this_object());
    set_wield_modifier("devotion_good", 20);
    add_property(({ "artifact", "good" }));
    add_property("wield_msg",
                 "You feel the presence of the holy warrior.\n");
    add_property("remove_msg", 
                 "You no longer feel the presence of the holy warrior.\n");
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
    add_hook("__reset", store_fp("on_reset"));
}

static void
on_wield(object obj, string hands) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->add_hook("__bdie", store_fp("prevent_death"));
}

static void
on_remove() 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->remove_hook("__bdie");
}

static void
on_reset(int flag) 
{
    object ply;
    if (!objectp(ply = query_wield()) || _life != 0) {
        return;
    }
    tell_object(ply, "You feel protected from death by the holy warrior!\n");
    _life = 1;
}

public int
prevent_death(object foe) 
{
    object ply;
    if (!objectp(ply = query_wield()) ||
        ply->query_alignment() < foe->query_alignment() ||
        _life == 0)
    {
        return 0;
    }
    tell_object(ply, bold("\nThe spirit of the holy warrior and " +
                          "the Lords of Order prevent your death!\n\n"));
    ply->heal_self(888);
    _life = 0;
    return 1;
}

public mixed
weapon_hit(object foe) 
{
    object ply;
    int val;
    if ((!objectp(ply = query_wield()) || !objectp(foe)) || 
        (interactive(ply) && ply->query_alignment() < foe->query_alignment()))
    {
        return "miss";
    }
    val = ply->query_tmp_prop("devotion_good"); 
    if ((_bias += val / 4 + random(val / 2)) >= 100) {
        _bias = 0; /* by devotion 10-50% chance */
        tell_object(ply, "Your hands are guided by the holy warrior!\n");
        return 87; /* average 34 dmg at level 29 */
    }
    return 47; /* average 24 dmg at level 29 */
}
