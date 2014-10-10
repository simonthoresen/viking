#include "/d/Empire/empire.h"

inherit weapon EMP_I_WEAPON;
inherit align  EMP_I_ALIGNED;

private int _bias;

static void
create()
{
    weapon::create();
    align::create();
    _bias = 0;

    set_name("Longsword of Akol");
    set_short("an incredibly thin longsword");
    set_long("This longsword's blade is incredibly thin. If you look at the " +
             "flat of the blade, it appears normal, but turn it sideways, " +
             "and the blade will be practically invisible. This remarkable " +
             "thinness also gives it awesome capabilities. It will most " +
             "likely ignore armour, simply cutting right through it.");
    set_info("This is the sword of the holy knight Akol.");
    add_id(({ "sword", "longsword", "thin longsword" }));
    set_class(9);
    set_weight(2);
    set_value(2222);
    set_damage_type("slash");
    set_min_align(ALIGN_GOOD);
    set_hit_func(this_object());
    set_wield_modifier("devotion_good", 20);
    add_hook("__break", store_fp("shatter_sword"));
    add_property(({ "artifact", "good" }));
    add_property("wield_msg", 
                 "You feel the guiding hands of the holy knight.\n");
    add_property("remove_msg", 
                 "You feel the guiding hands of the holy knight slip away.\n");
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
        tell_object(ply, "Your hands are guided by the holy knight!\n");
        EMP_D_COMBAT->hit_player(ply, foe, 20 + 2 * foe->query_ac(), 
                                 ({ "Slash", "Chop", "Pierce" })[random(3)]);
        if (!objectp(foe)) {
            return "miss";
        }
    }
    return 22 + 2 * foe->query_ac(); /* average 15 dmg at level 29 */
}

static void
shatter_sword(string type, int dmg) 
{
    object env;
    if (objectp(env = environment())) {
        message("", "The longsword shatters into a thousand pieces.\n", env);
    }
    call_out("destroy", 0);
}

public int
is_good() 
{
    return 1;
}
