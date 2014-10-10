#include "/d/Empire/islands/reikland.h"

inherit weapon EMP_I_WEAPON;
inherit align  EMP_I_ALIGNED;

private int _bias;

static void
create() 
{
    weapon::create();
    align::create();
    _bias = 0;

    set_name("Scythe of Bloody Reaping");
    set_short("a razor-sharp scythe");
    set_long("A short wooden shaft with a razor-sharp curved blade mounted " +
             "at the lower end. The blade is smeared with blood.");
    add_id("scythe");
    set_class(19);
    set_weight(4);
    set_value(2222);
    set_damage_type(({ "claw", "slash" }));
    set_max_align(ALIGN_EVIL);
    set_hit_func(this_object());
    set_wield_modifier("devotion_evil", 20);
    add_property(({ "artifact", "evil" }));
    add_property("wield_msg", "The razorsharp edge of the scyth makes you " +
                 "nervous just by holding it.\n");
    add_property("remove_msg", "You feel less nervous.\n");
}

static void
cut_player(object foe) 
{
    object ply;
    if (!objectp(foe) ||
        !objectp(ply = query_wield()))
    {
        return;
    }
    if (EMP_D_COMBAT->hit_player(ply, foe, 10 + random(10), 
                                 "slash", 0, this_object()) > 5) 
    {
        EMP_D_COMBAT->wound_player(ply, foe, 10 + random(10));
    }
}

public mixed
weapon_hit(object foe) 
{
    object ply;
    int val;
    if ((!objectp(ply = query_wield()) || !objectp(foe)) || 
        (interactive(ply) && ply->query_alignment() > foe->query_alignment()))
    {
        return "miss";
    }
    val = ply->query_tmp_prop("devotion_evil");
    if ((_bias += val / 4 + random(val / 2)) >= 100) {
        _bias = 0; /* by devotion 10-50% chance */
        tell_object(ply, "Your hands are forced by the demon lord!\n");
        map_array(ply->query_attackers(), "cut_player");
    }
    return 44; /* avg 23 dmg at level 29 */
}
